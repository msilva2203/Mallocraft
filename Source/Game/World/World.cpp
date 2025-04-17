/**
 * @file World.cpp
 * @author Marco Silva (msilva2203)
 */

#include "World.h"
#include "Framework/Instance.h"
#include "Framework/Pawn.h"
#include "Chunk.h"

#define CHUNK_NUM (3 * 2 + 1)

static i32 NumChunksRemeshed = 0;

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
            SpawnChunk(Id);
        }
    }
}

void World::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);

    NumChunksRemeshed = 0;

    Pawn* CurrentPawn = GetInstance()->GetPlayerController()->GetPawn();
    if (!CurrentPawn) return;

    // Check if pawn changed chunk and spawn chunks if necessary
    glm::ivec2 PawnGridPosition = glm::ivec2(0);
    PawnGridPosition.x = (i32)std::floor(CurrentPawn->GetPosition().x / CHUNK_SIZE);
    PawnGridPosition.y = (i32)std::floor(CurrentPawn->GetPosition().z / CHUNK_SIZE);
    i64 PawnChunkId = MakeChunkId(PawnGridPosition);
    if (PawnChunkId != LastPawnChunkId) {
        SpawnChunk(PawnChunkId);
    }
    LastPawnChunkId = PawnChunkId;

    // Create chunks in queue
    i32 FrameGenNum = 2;
    for (i32 i = 0; i < FrameGenNum; i++) {
        if (!ChunkQueue.empty()) {
            i64 ChunkId = ChunkQueue.front();
            ChunkQueue.pop();
            InQueue.erase(ChunkId);
            CreateChunk(ChunkId);
        } else {
            break;
        }
    }
    
    // Update chunks
    for (auto It : LoadedChunks) {
        It->Update(DeltaTime);
    }

    std::cout << NumChunksRemeshed << std::endl;
}

void World::Draw() {
    Super::Draw();

    for (auto It : LoadedChunks) {
        It->Draw();
    }
}

void World::SpawnChunk(const i64 ChunkId) {
    if (ChunkMapping.find(ChunkId) != ChunkMapping.end()) {
        return;
    }
    ChunkQueue.push(ChunkId);
    InQueue.insert(ChunkId);
}

Chunk* World::CreateChunk(const i64 ChunkId) {
    Chunk* NewChunk = new Chunk(this);
    NewChunk->GenerateData(ChunkId);

    LoadedChunks.push_back(NewChunk);
    ChunkMapping[ChunkId] = NewChunk;

    GenerateChunkMesh(NewChunk);

    return NewChunk;
}

Chunk* World::GetChunk(const i64 ChunkId) {
    auto It = ChunkMapping.find(ChunkId);
    if (It != ChunkMapping.end()) {
        return It->second;
    }
    return nullptr;
}

void World::GenerateChunkMesh(Chunk* InChunk) {
    if (!InChunk) return;

    static std::array<glm::ivec2, 4> Directions = {
        glm::ivec2(-1,  0),
        glm::ivec2( 1,  0),
        glm::ivec2( 0, -1),
        glm::ivec2( 0,  1)
    };

    InChunk->GenerateMesh();
    NumChunksRemeshed++;
    for (auto Dir : Directions) {
        glm::ivec2 GridPosition = MakeChunkPosition(InChunk->GetId());
        GridPosition.x += Dir.x;
        GridPosition.y += Dir.y;
        i64 NeighborId = MakeChunkId(GridPosition);
        Chunk* NeighborChunk = GetChunk(NeighborId);
        if (NeighborChunk) {
            NeighborChunk->GenerateMesh();
            NumChunksRemeshed++;
        }
    }
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