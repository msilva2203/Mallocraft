/**
 * @file World.cpp
 * @author Marco Silva (msilva2203)
 */

#include "World.h"
#include "Framework/Instance.h"
#include "Framework/Pawn.h"
#include "Chunk.h"

#define CHUNK_NUM 9

static inline u64 EncodeInt(i32 v) {
    return (v >= 0) ? (2 * static_cast<u64>(v)) : (2 * static_cast<u64>(-v) - 1);
}

static inline i32 DecodeInt(u64 v) {
    return (v % 2 == 0) ? static_cast<i32>(v / 2) : -static_cast<i32>((v + 1) / 2);
}

World::World() {

}

World::~World() {

}

void World::Setup() {
    Super::Setup();

    for (i32 i = 0; i < CHUNK_NUM; i++) {
        for (i32 j = 0; j < CHUNK_NUM; j++) {
            glm::ivec2 Position = glm::ivec2(i, j);
            i64 Id = MakeChunkId(Position);
            Chunk* NewChunk = new Chunk(this);

            LoadedChunks.push_back(NewChunk);
            ChunkMapping[Id] = NewChunk;

            NewChunk->GenerateData(Id);
        }
    }

    for (auto It : LoadedChunks) {
        It->GenerateMesh();
    }
}

void World::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);

    Pawn* CurrentPawn = GetInstance()->GetPlayerController()->GetPawn();
    if (!CurrentPawn) return;

    for (auto It : LoadedChunks) {
        It->Update(DeltaTime);
    }
}

void World::Draw() {
    Super::Draw();

    for (auto It : LoadedChunks) {
        It->Draw();
    }
}

Chunk* World::GetChunk(const i64 ChunkId) {
    auto It = ChunkMapping.find(ChunkId);
    if (It != ChunkMapping.end()) {
        return It->second;
    }
    return nullptr;
}

i64 World::MakeChunkId(const glm::ivec2& Position) {
    u64 x = EncodeInt(Position.x);
    u64 y = EncodeInt(Position.y);
    return (x + y) * (x + y + 1) / 2 + y;
}

glm::ivec2 World::MakeChunkPosition(const i64 Id) {
    u64 w = static_cast<int>((std::sqrt(8 * Id + 1) - 1) / 2);
    u64 t = (w * w + w) / 2;
    u64 y = Id - t;
    u64 x = w - y;
    return glm::ivec2(DecodeInt(x), DecodeInt(y));
}