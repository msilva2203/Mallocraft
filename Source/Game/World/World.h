/**
 * @file World.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Framework/Entity.h"
#include <unordered_map>
#include <queue>
#include <set>

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

    void SpawnChunk(const i64 ChunkId);
    Chunk* CreateChunk(const i64 ChunkId);
    Chunk* GetChunk(i64 ChunkId);

    void GenerateChunkMesh(Chunk* InChunk);

    static i64 MakeChunkId(const glm::ivec2& Position);
    static glm::ivec2 MakeChunkPosition(const i64 Id);

private:

    std::vector<Chunk*> LoadedChunks;
    std::unordered_map<i64, Chunk*> ChunkMapping;
    std::queue<i64> ChunkQueue;
    std::set<i64> InQueue;

    i64 LastPawnChunkId = -999;

};