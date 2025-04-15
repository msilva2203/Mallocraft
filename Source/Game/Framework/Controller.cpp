/**
 * @file Controller.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Controller.h"
#include "Pawn.h"

Controller::Controller() {

}

Controller::~Controller() {
    
}

void Controller::Setup() {
    Super::Setup();

}

void Controller::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);

}

void Controller::Draw() {
    Super::Draw();
}

Pawn* Controller::GetPawn() const {
    return PossessedPawn;
}

void Controller::PossessPawn(Pawn* NewValue) {
    if (NewValue == nullptr) {
        return;
    }
    if (PossessedPawn) {
        UnPossessPawn();
    }
    PossessedPawn = NewValue;
    PossessedPawn->Possess(this);
}

void Controller::UnPossessPawn() {
    if (PossessedPawn) {
        PossessedPawn->UnPossess(this);
    }
    PossessedPawn = nullptr;
}

bool Controller::IsPlayerController() const {
    return false;
}