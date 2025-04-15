/**
 * @file Controller.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Entity.h"

class Pawn;

class Controller : public Entity
{
    using Super = Entity;
public:

    Controller();
    virtual ~Controller();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

    Pawn* GetPawn() const;
    void PossessPawn(Pawn* NewValue);
    void UnPossessPawn();

    virtual bool IsPlayerController() const;

private:

    Pawn* PossessedPawn = nullptr;

};