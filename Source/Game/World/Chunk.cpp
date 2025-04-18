/**
 * @file Chunk.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Chunk.h"
#include "GLFW/glfw3.h"

static constexpr i32 Mod(i32 A, i32 B) {
    return (A % B + B) % B;
}

Chunk::Chunk(World* InWorld) {
    OwningWorld = InWorld;

    VAO = new VertexArray();
    VAO->Bind();

    VBO = new VertexBuffer();
    VBO->Bind();

    // Get reference to shader and texture
    ChunkShader = Shader::Manager::GetShader("Content/Shaders/Chunk.glsl");
    ChunkTexture = Texture::Manager::GetTexture("Content/Textures/Atlas.jpg");
}

Chunk::~Chunk() {
    delete VAO;
    delete VBO;
}

void Chunk::Setup() {

}

void Chunk::Update(f32 DeltaTime) {
    
}

void Chunk::Draw() {
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::translate(Model, GetPosition());

    ChunkShader->Bind();
    ChunkShader->SetFloatMatrix4("uModel", Model);
    ChunkTexture->Bind();
    VAO->Bind();

    glDrawArrays(GL_TRIANGLES, 0, Size);
}

void Chunk::GenerateData(const i64 InId) {
    Id = InId;

    glm::ivec2 ChunkGridPosition = World::MakeChunkPosition(Id);
    glm::vec3 ChunkWorldPosition = glm::vec3( ChunkGridPosition.x * CHUNK_SIZE, 0.0f, ChunkGridPosition.y * CHUNK_SIZE );
    SetPosition(ChunkWorldPosition);

    for (i32 X = 0; X < CHUNK_SIZE; X++) {
        for (i32 Y = 0; Y < CHUNK_HEIGHT; Y++) {
            for (i32 Z = 0; Z < CHUNK_SIZE; Z++) {
                const glm::ivec3 BlockPosition = glm::ivec3(
                    ChunkWorldPosition.x + X,
                    ChunkWorldPosition.y + Y,
                    ChunkWorldPosition.z + Z
                );
                Blocks[X][Y][Z] = OwningWorld->GenerateBlock(BlockPosition);
            }
        }
    }
}

void Chunk::GenerateMesh() {
    static std::array<glm::ivec3, 6> Directions = {
        glm::ivec3( -1,  0,  0 ),
        glm::ivec3(  1,  0,  0 ),
        glm::ivec3(  0,  1,  0 ),
        glm::ivec3(  0, -1,  0 ),
        glm::ivec3(  0,  0, -1 ),
        glm::ivec3(  0,  0,  1 )
    };

    static std::array<std::array<glm::ivec3, 6>, 6> Faces = {{
        // Front face (x = 0)
        {
            glm::ivec3(0, 0, 0),
            glm::ivec3(0, 0, 1),
            glm::ivec3(0, 1, 1),
            glm::ivec3(0, 1, 1),
            glm::ivec3(0, 1, 0),
            glm::ivec3(0, 0, 0)
        },
        // Back face (x = 1)
        {
            glm::ivec3(1, 0, 1),
            glm::ivec3(1, 0, 0),
            glm::ivec3(1, 1, 0),
            glm::ivec3(1, 1, 0),
            glm::ivec3(1, 1, 1),
            glm::ivec3(1, 0, 1)
        },
        // Top face (y = 1)
        {
            glm::ivec3(0, 1, 0),
            glm::ivec3(0, 1, 1),
            glm::ivec3(1, 1, 1),
            glm::ivec3(1, 1, 1),
            glm::ivec3(1, 1, 0),
            glm::ivec3(0, 1, 0)
        },
        // Bottom face (y = 0)
        {
            glm::ivec3(1, 0, 0),
            glm::ivec3(1, 0, 1),
            glm::ivec3(0, 0, 1),
            glm::ivec3(0, 0, 1),
            glm::ivec3(0, 0, 0),
            glm::ivec3(1, 0, 0)
        },
        // Left face (z = 0)
        {
            glm::ivec3(1, 0, 0),
            glm::ivec3(0, 0, 0),
            glm::ivec3(0, 1, 0),
            glm::ivec3(0, 1, 0),
            glm::ivec3(1, 1, 0),
            glm::ivec3(1, 0, 0)
        },
        // Right face (z = 1)
        {
            glm::ivec3(0, 0, 1),
            glm::ivec3(1, 0, 1),
            glm::ivec3(1, 1, 1),
            glm::ivec3(1, 1, 1),
            glm::ivec3(0, 1, 1),
            glm::ivec3(0, 0, 1)
        }
    }};

    static std::array<glm::ivec2, 6> Uvs = {
        glm::ivec2(0.0f, 0.0f),
        glm::ivec2(1.0f, 0.0f),
        glm::ivec2(1.0f, 1.0f),
        glm::ivec2(1.0f, 1.0f),
        glm::ivec2(0.0f, 1.0f),
        glm::ivec2(0.0f, 0.0f),
    };

    static std::array<f32, 6> LightLevels = {
        0.65f,
        0.65f,
        1.00f,
        1.00f,
        0.90f,
        0.90f
    };

    auto GridPosition = World::MakeChunkPosition(Id);
    
    std::vector<f32> MeshData;

    for (i32 X = 0; X < CHUNK_SIZE; X++) {
        for (i32 Y = 0; Y < CHUNK_HEIGHT; Y++) {
            for (i32 Z = 0; Z < CHUNK_SIZE; Z++) {

                // Get iteration block and ignore it if air
                Blocks::Type ItBlock = Blocks[X][Y][Z];
                if (ItBlock == Blocks::Type::Air) continue;
                
                // Generate each mesh of the block
                i32 FaceIndex = 0;
                for (auto& Dir : Directions) {
                    auto& FaceData = Faces[FaceIndex];

                    Direction ItDirection = (Direction)FaceIndex;

                    Blocks::Type NeighborBlock = Blocks::Type::Air;
                    glm::ivec3 Neighbor( X + Dir.x, Y + Dir.y, Z + Dir.z );

                    if (!IsInChunk(Neighbor)) {
                        // Gets the block from the neighbor chunk
                        glm::ivec2 NeighborGridPosition = glm::ivec2( GridPosition.x + Dir.x, GridPosition.y + Dir.z );
                        i64 NeighborId = World::MakeChunkId(NeighborGridPosition);
                        Chunk* NeighborChunk = OwningWorld->GetChunk(NeighborId);
                        if (NeighborChunk) {
                            Neighbor.x = Mod(Neighbor.x, CHUNK_SIZE);
                            Neighbor.z = Mod(Neighbor.z, CHUNK_SIZE);
                            NeighborBlock = NeighborChunk->GetBlockAt(Neighbor);
                        }
                    } else {
                        // Gets the block from this chunk
                        NeighborBlock = GetBlockAt(Neighbor);
                    }

                    // Add the face to the mesh
                    if (NeighborBlock == Blocks::Type::Air) {
                        i32 VertexIndex = 0;
                        for (auto& Vertex : FaceData) {
                            auto Uv = Uvs[VertexIndex];
                            MeshData.push_back(Vertex.x + X);
                            MeshData.push_back(Vertex.y + Y);
                            MeshData.push_back(Vertex.z + Z);
                            MeshData.push_back(Uv.x);
                            MeshData.push_back(Uv.y);
                            MeshData.push_back(Blocks::GetTextureIndex(ItBlock, ItDirection));
                            MeshData.push_back(LightLevels[FaceIndex]);
                            VertexIndex++;
                        }
                    }
                    FaceIndex++;
                }

            }
        }
    }

    VAO->Bind();
    VBO->Bind();

    Size = MeshData.size() / 7;
    VBO->BufferData(MeshData.data(), sizeof(f32) * MeshData.size(), 7 * sizeof(f32));
    VBO->AddAttribute(3);
    VBO->AddAttribute(2);
    VBO->AddAttribute(1);
    VBO->AddAttribute(1);

    VAO->Unbind();
    VBO->Unbind();
}

bool Chunk::IsInChunk(const glm::ivec3& RelativePos) {
    if (RelativePos.x < 0 || RelativePos.x >= CHUNK_SIZE)   return false;
    if (RelativePos.z < 0 || RelativePos.z >= CHUNK_SIZE) return false;
    return true;
}

Blocks::Type Chunk::GetBlockAt(const glm::ivec3& RelativePos) {
    if (RelativePos.y < 0 || RelativePos.y >= CHUNK_HEIGHT) {
        return Blocks::Type::Air;
    }
    return Blocks[RelativePos.x][RelativePos.y][RelativePos.z];
}