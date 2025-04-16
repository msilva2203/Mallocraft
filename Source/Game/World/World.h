/**
 * @file World.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Framework/Entity.h"
#include <unordered_map>

class Chunk;

class World : public Entity
{
    using Super = Entity;
public:

    World();
    virtual ~World();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

    Chunk* GetChunk(i64 ChunkId);

    static i64 MakeChunkId(const glm::ivec2& Position);
    static glm::ivec2 MakeChunkPosition(const i64 Id);

private:

    std::vector<Chunk*> LoadedChunks;
    std::unordered_map<i64, Chunk*> ChunkMapping;

};