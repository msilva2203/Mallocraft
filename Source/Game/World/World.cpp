/**
 * @file World.cpp
 * @author Marco Silva (msilva2203)
 */

#include "World.h"
#include "Framework/Instance.h"
#include "Framework/Pawn.h"
#include "Chunk.h"

#define CHUNK_NUM (9 * 2 + 1)

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

    //goto gen;

    // Check if pawn changed chunk and spawn chunks if necessary
    glm::ivec2 PawnGridPosition = glm::ivec2(0);
    PawnGridPosition.x = (i32)std::floor(CurrentPawn->GetPosition().x / CHUNK_SIZE);
    PawnGridPosition.y = (i32)std::floor(CurrentPawn->GetPosition().z / CHUNK_SIZE);
    i64 PawnChunkId = MakeChunkId(PawnGridPosition);
    if (PawnChunkId != LastPawnChunkId) {
        i32 ViewDistance = 9;
        for (i32 i = PawnGridPosition.x - ViewDistance; i < PawnGridPosition.x + ViewDistance; i++) {
            for (i32 j = PawnGridPosition.y - ViewDistance; j < PawnGridPosition.y + ViewDistance; j++) {
                i64 Id = MakeChunkId(glm::ivec2(i, j));
                SpawnChunk(Id);
            }
        }
        //SpawnChunk(PawnChunkId);
    }
    LastPawnChunkId = PawnChunkId;

    gen:
    // Create chunks in queue
    i32 FrameGenNum = 1;
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

Blocks::Type World::GenerateBlock(const glm::ivec3& Position) {
    const i32 SurfaceLevel = 120;
    const i32 WaterLevel = 100;

    f32 Frequency = 0.02f;
    f32 Amplitude = 20.0f;
    f32 TerrainLevel = SurfaceLevel 
        + glm::sin(Position.x * Frequency) * Amplitude 
        + glm::sin(Position.x * Frequency * 4.0f) * Amplitude * 0.25f
        + glm::sin(Position.x * Frequency * 8.0f) * Amplitude * (1.0f/8.0f)
        + glm::sin(Position.x * Frequency * 16.0f) * Amplitude * (1.0f/16.0f)
        + glm::sin(Position.x * Frequency * 32.0f) * Amplitude * (1.0f/32.0f)
        + glm::sin(Position.z * Frequency) * Amplitude
        + glm::sin(Position.z * Frequency * 4.0f) * Amplitude * 0.25f
        + glm::sin(Position.z * Frequency * 8.0f) * Amplitude * (1.0f/8.0f)
        + glm::sin(Position.z * Frequency * 16.0f) * Amplitude * (1.0f/16.0f)
        + glm::sin(Position.z * Frequency * 32.0f) * Amplitude * (1.0f/32.0f);

    if (Position.y < TerrainLevel - 1) {
        // Stone
        return Blocks::Type::Stone;
    } else if (Position.y <= TerrainLevel) {
        // Dirt
        return Blocks::Type::Dirt;
    } else if (Position.y < WaterLevel) {
        // Water
        return Blocks::Type::Air;
    }

    return Blocks::Type::Air;
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