/**
 * @file Pawn.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Entity.h"
#include "Input.h"

class Controller;
class PlayerController;

class Pawn : public Entity, public InputListener
{
    using Super = Entity;
public:

    Pawn();
    virtual ~Pawn();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

    virtual void Possess(Controller* InController);
    virtual void UnPossess(Controller* InController);

    virtual void OnKeyPressed(Input::Key InKey) override {}
    virtual void OnKeyReleased(Input::Key InKey) override {}
    virtual void OnMouseMoved(f64 OffsetX, f64 OffsetY) override {}

    Controller* GetController() const;
    PlayerController* GetPlayerController() const;

private:

    Controller* PossessingController = nullptr;

};