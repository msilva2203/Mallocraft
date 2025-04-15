/**
 * @file Instance.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Instance.h"

Instance::Instance() {

}

Instance::~Instance() {
    for (auto It : Entities) {
        delete It;
    }
}

void Instance::Setup() {
    PC = CreateEntity<PlayerController>();
}

void Instance::Update(f32 DeltaTime) {
    while (!PendingEntities.empty()) {
        Entity* NewEntity = PendingEntities.front();
        Entities.push_back(NewEntity);
        NewEntity->CurrentInstance = this;
        NewEntity->Setup();
        PendingEntities.pop();
    }

    for (auto It : Entities) {
        It->Update(DeltaTime);
    }

    if (PC) {
        PC->UpdateView();
    }
}

void Instance::Draw() {
    for (auto It : Entities) {
        It->Draw();
    }
}

void Instance::RegisterInputListener(InputListener* NewInputListener) {
    InputListeners.push_back(NewInputListener);
}

void Instance::OnKeyPressed(Input::Key InKey) {
    for (auto It : InputListeners) {
        It->OnKeyPressed(InKey);
    }
}

void Instance::OnKeyReleased(Input::Key InKey) {
    for (auto It : InputListeners) {
        It->OnKeyReleased(InKey);
    }
}

void Instance::OnMouseMoved(f64 OffsetX, f64 OffsetY) {
    for (auto It : InputListeners) {
        It->OnMouseMoved(OffsetX, OffsetY);
    }
}

PlayerController* Instance::GetPlayerController() const {
    return PC;
}