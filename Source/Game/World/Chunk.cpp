/**
 * @file Chunk.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Chunk.h"
#include "GLFW/glfw3.h"

Chunk::Chunk() {
    
}

Chunk::~Chunk() {
    delete VAO;
    delete VBO;
}

void Chunk::Setup() {
    VAO = new VertexArray();
    VAO->Bind();

    VBO = new VertexBuffer();
    VBO->Bind();

    ChunkShader = Shader::Manager::GetShader("Content/Shaders/Chunk.glsl");

    for (i32 X = 0; X < CHUNK_SIZE; X++) {
        for (i32 Y = 0; Y < CHUNK_HEIGHT; Y++) {
            for (i32 Z = 0; Z < CHUNK_SIZE; Z++) {
                i32 Height = (glm::sin(glm::radians((f32)X * (f32)Z) * 2) * 4) + (CHUNK_HEIGHT / 6);
                if (Y < Height)
                    Blocks[X][Y][Z] = 1;
            }
        }
    }

    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(16.0f, 0.0f, 0.0f));

    ChunkShader->Bind();
    ChunkShader->SetFloatMatrix4("uModel", Model);

    ChunkTexture = new Texture();
    ChunkTexture->Load("Content/Textures/Placeholder.jpg");

    GenerateMesh();
}

void Chunk::Update(f32 DeltaTime) {
    Time += DeltaTime;
    if (Time >= 0.1f) {
        std::cout << "Generating new chunk!" << std::endl;
        glm::ivec3 IndexCoord = glm::ivec3( Index % CHUNK_SIZE, (Index / CHUNK_SIZE) % CHUNK_HEIGHT, Index / (CHUNK_SIZE * CHUNK_HEIGHT) );
        Blocks[IndexCoord.x][IndexCoord.y][IndexCoord.z] = 0;
        Index++;
        GenerateMesh();
        Time = 0.0f;
    }
}

void Chunk::Draw() {
    ChunkShader->Bind();
    ChunkTexture->Bind();
    VAO->Bind();

    glDrawArrays(GL_TRIANGLES, 0, Size);
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
    
    std::vector<f32> MeshData;

    for (i32 X = 0; X < CHUNK_SIZE; X++) {
        for (i32 Y = 0; Y < CHUNK_HEIGHT; Y++) {
            for (i32 Z = 0; Z < CHUNK_SIZE; Z++) {

                if (Blocks[X][Y][Z] == 0) continue;
                
                i32 FaceIndex = 0;
                for (auto& Dir : Directions) {
                    auto& FaceData = Faces[FaceIndex];

                    glm::ivec3 Neighbor( X + Dir.x, Y + Dir.y, Z + Dir.z );
                    if (!IsInChunk(Neighbor) || GetBlockAt(Neighbor) == 0) {

                        i32 VertexIndex = 0;
                        for (auto& Vertex : FaceData) {
                            auto Uv = Uvs[VertexIndex];
                            MeshData.push_back(Vertex.x + X);
                            MeshData.push_back(Vertex.y + Y);
                            MeshData.push_back(Vertex.z + Z);
                            MeshData.push_back(Uv.x);
                            MeshData.push_back(Uv.y);
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

    Size = MeshData.size() / 5;
    VBO->BufferData(MeshData.data(), sizeof(f32) * MeshData.size(), 5 * sizeof(f32));
    VBO->AddAttribute(3);
    VBO->AddAttribute(2);

    VAO->Unbind();
    VBO->Unbind();
}

bool Chunk::IsInChunk(const glm::ivec3& RelativePos) {
    if (RelativePos.x < 0 || RelativePos.x >= CHUNK_SIZE)   return false;
    if (RelativePos.y < 0 || RelativePos.y >= CHUNK_HEIGHT)   return false;
    if (RelativePos.z < 0 || RelativePos.z >= CHUNK_SIZE) return false;
    return true;
}

u64 Chunk::GetBlockAt(const glm::ivec3& RelativePos) {
    return Blocks[RelativePos.x][RelativePos.y][RelativePos.z];
}