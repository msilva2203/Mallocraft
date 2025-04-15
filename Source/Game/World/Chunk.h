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
#include <array>

#define CHUNK_SIZE        (16)
#define CHUNK_HEIGHT      (258)

class Chunk : public Entity
{
public:

    Chunk();
    virtual ~Chunk();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

    void GenerateMesh();

private:

    bool IsInChunk(const glm::ivec3& RelativePos);
    u64 GetBlockAt(const glm::ivec3& RelativePos);

    u64 Blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE] = { 0 };

    VertexArray* VAO;
    VertexBuffer* VBO;
    u64 Size;

    Shader* ChunkShader;
    Texture* ChunkTexture;

    i32 Index = 0;
    f32 Time = 0.0f;
};