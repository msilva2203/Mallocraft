/**
 * @file Chunk.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/ElementsBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/Renderer.h"
#include "Framework/Entity.h"
#include "World.h"
#include "Blocks.h"
#include <array>

#define CHUNK_SIZE        (16)
#define CHUNK_HEIGHT      (256)

class Chunk : public Entity
{
public:

    Chunk(World* InWorld);
    virtual ~Chunk();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

    void GenerateData(const i64 InId);
    void GenerateMesh();

    i64 GetId() const { return Id; }

private:

    bool IsInChunk(const glm::ivec3& RelativePos);
    Blocks::Type GetBlockAt(const glm::ivec3& RelativePos);

    World* OwningWorld;
    Blocks::Type Blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    i64 Id;

    VertexArray* VAO;
    VertexBuffer* VBO;
    u64 Size;

    Shader* ChunkShader;
    Texture* ChunkTexture;
    
};