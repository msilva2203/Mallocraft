/**
 * @file SandboxInstance.cpp
 * @author Marco Silva (msilva2203)
 */

#include "SandboxInstance.h"
#include "Entities/CubeTest.h"
#include "PlayerPawn.h"
#include "World/World.h"

void SandboxInstance::Setup() {
    Super::Setup();

    CreateEntity<CubeTest>()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    CreateEntity<CubeTest>()->SetPosition(glm::vec3(16.0f, 0.0f, 0.0f));
    CreateEntity<CubeTest>()->SetPosition(glm::vec3(0.0f, 0.0f, 16.0f));
    CreateEntity<PlayerPawn>();
    CreateEntity<World>();
}