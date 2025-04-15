/**
 * @file Instance.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Entity.h"
#include "PlayerController.h"
#include "Input.h"

#include <vector>
#include <queue>

class Entity;
class PlayerController;

class Instance : public InputListener {
public:

    Instance();
    virtual ~Instance();

    virtual void Setup();
    void Update(f32 DeltaTime);
    void Draw();

    void RegisterInputListener(InputListener* NewInputListener);
    virtual void OnKeyPressed(Input::Key InKey) override;
    virtual void OnKeyReleased(Input::Key InKey) override;
    virtual void OnMouseMoved(f64 OffsetX, f64 OffsetY) override;

    template <typename T>
    T* CreateEntity() {
        T* NewEntity = new T();
        PendingEntities.push(NewEntity);
        return NewEntity;
    }

    PlayerController* GetPlayerController() const;

private:

    std::vector<Entity*> Entities;
    std::queue<Entity*> PendingEntities;
    std::vector<InputListener*> InputListeners;

    PlayerController* PC;

};