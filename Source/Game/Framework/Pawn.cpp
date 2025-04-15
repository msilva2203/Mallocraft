/**
 * @file Pawn.cpp 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Pawn.h"
#include "Controller.h"
#include "PlayerController.h"

Pawn::Pawn() {

}

Pawn::~Pawn() {

}

void Pawn::Setup() {
    Super::Setup();

}

void Pawn::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);

}

void Pawn::Draw() {
    Super::Draw();

}

void Pawn::Possess(Controller* InController) {
    PossessingController = InController;
}

void Pawn::UnPossess(Controller* InController) {
    PossessingController = nullptr;
}

Controller* Pawn::GetController() const {
    return PossessingController;
}

PlayerController* Pawn::GetPlayerController() const {
    if (GetController() && GetController()->IsPlayerController()) {
        return static_cast<PlayerController*>(GetController());
    }
    return nullptr;
}