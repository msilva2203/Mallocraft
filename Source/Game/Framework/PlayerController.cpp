/**
 * @file PlayerController.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "PlayerController.h"
#include "Rendering/Shader.h"
#include "Pawn.h"
#include "Instance.h"
#include "Globals.h"
#include "Rendering/Window.h"

PlayerController::PlayerController() {

}

PlayerController::~PlayerController() {

}

void PlayerController::Setup() {
    Super::Setup();

    GetInstance()->RegisterInputListener(this);
}

void PlayerController::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);

}

void PlayerController::Draw() {
    Super::Draw();
    
}

void PlayerController::OnKeyPressed(Input::Key InKey) {
    Pawn* CurrentPawn = GetPawn();
    if (CurrentPawn) {
        CurrentPawn->OnKeyPressed(InKey);
    }

    switch (InKey) {
        case Input::Key::ESC: {
            Globals::AppWindow->Close();
            break;
        }
        default: {
            break;
        }
    }
}

void PlayerController::OnKeyReleased(Input::Key InKey) {
    Pawn* CurrentPawn = GetPawn();
    if (CurrentPawn) {
        CurrentPawn->OnKeyReleased(InKey);
    }
}

void PlayerController::OnMouseMoved(f64 OffsetX, f64 OffsetY) {
    Pawn* CurrentPawn = GetPawn();
    if (CurrentPawn) {
        CurrentPawn->OnMouseMoved(OffsetX, OffsetY);
    }
}

bool PlayerController::IsPlayerController() const {
    return true;
}

void PlayerController::SetViewCamera(Camera* NewValue) {
    if (NewValue == nullptr) {
        return;
    }
    ViewCamera = NewValue;
}

Camera* PlayerController::GetViewCamera() const {
    return ViewCamera;
}

void PlayerController::UpdateView() {
    if (!ViewCamera) return;
    glm::mat4 ViewMatrix = ViewCamera->GetViewMatrix();
    glm::mat4 ProjectionMatrix = ViewCamera->GetProjectionMatrix();
    for (auto ItShader : Shader::Manager::GetShaders()) {
        ItShader->Bind();
        ItShader->SetFloatMatrix4("uView", ViewMatrix);
        ItShader->SetFloatMatrix4("uProjection", ProjectionMatrix);
        ItShader->Unbind();
    }
}