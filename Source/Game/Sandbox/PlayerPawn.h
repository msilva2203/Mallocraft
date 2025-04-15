/**
 * @file PlayerPawn.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Framework/Pawn.h"
#include "Framework/PlayerController.h"

class Camera;

class PlayerPawn : public Pawn {
    using Super = Pawn;
public:

    PlayerPawn();
    virtual ~PlayerPawn();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

    virtual void OnKeyPressed(Input::Key InKey) override;
    virtual void OnKeyReleased(Input::Key InKey) override;
    virtual void OnMouseMoved(f64 OffsetX, f64 OffsetY) override;

    virtual void Possess(Controller* InController) override;
    virtual void UnPossess(Controller* InController) override;

private:

    Camera* MainCamera = nullptr;

};