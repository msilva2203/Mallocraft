/**
 * @file PlayerPawn.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "PlayerPawn.h"
#include "Framework/Camera.h"
#include "Framework/Instance.h"
#include "Input.h"
#include "GLFW/glfw3.h"

PlayerPawn::PlayerPawn() {

}

PlayerPawn::~PlayerPawn() {

}

void PlayerPawn::Setup() {
    Super::Setup();

    GetInstance()->GetPlayerController()->PossessPawn(this);

    MainCamera = GetInstance()->CreateEntity<Camera>();
    GetPlayerController()->SetViewCamera(MainCamera);

    Input::SetMode(Input::Mode::Game);
}

void PlayerPawn::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);
    
    const f32 Speed = 5.0f;
    const glm::vec3 UpDirection = MainCamera->GetCameraUpDirection();
    const glm::vec3 ForwardDirection = MainCamera->GetCameraForwardDirection();
    const glm::vec3 RightDirection = MainCamera->GetCameraRightDirection();

    glm::vec3 InputVector = glm::vec3(0.0f);

    if (Input::IsKeyDown(Input::Key::W)) {
        InputVector += ForwardDirection * Speed * DeltaTime;
    }
    if (Input::IsKeyDown(Input::Key::S)) {
        InputVector -= ForwardDirection * Speed * DeltaTime;
    }
    if (Input::IsKeyDown(Input::Key::A)) {
        InputVector -= RightDirection * Speed * DeltaTime;
    }
    if (Input::IsKeyDown(Input::Key::D)) {
        InputVector += RightDirection * Speed * DeltaTime;
    }
    if (Input::IsKeyDown(Input::Key::SPACE)) {
        InputVector += UpDirection * Speed * DeltaTime;
    }
    if (Input::IsKeyDown(Input::Key::LSHIFT)) {
        InputVector -= UpDirection * Speed * DeltaTime;
    }

    SetPosition(GetPosition() + InputVector);
    MainCamera->SetPosition(GetPosition());
}

void PlayerPawn::Draw() {
    Super::Draw();

}

void PlayerPawn::OnKeyPressed(Input::Key InKey) {
    
}

void PlayerPawn::OnKeyReleased(Input::Key InKey) {

}

void PlayerPawn::OnMouseMoved(f64 OffsetX, f64 OffsetY) {
    f64 Sensitivity = 0.1f;
    OffsetX *= Sensitivity;
    OffsetY *= Sensitivity;

    glm::vec3 CameraRotation = MainCamera->GetRotation();
    CameraRotation.z += (f32)OffsetX;
    CameraRotation.y += (f32)OffsetY;

    if (CameraRotation.y > 89) {
        CameraRotation.y = 89;
    } else if (CameraRotation.y < -89) {
        CameraRotation.y = -89;
    }

    MainCamera->SetRotation(CameraRotation);
}

void PlayerPawn::Possess(Controller* InController) {
    Super::Possess(InController);

}

void PlayerPawn::UnPossess(Controller* InController) {
    Super::UnPossess(InController);

}