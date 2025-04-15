/**
 * @file Entity.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

class Instance;

class Entity
{
public:

    Entity();
    virtual ~Entity();

    virtual void Setup();
    virtual void Update(f32 DeltaTime);
    virtual void Draw();

    Instance* GetInstance() const;

    virtual void SetPosition(const glm::vec3& NewValue);
    virtual void SetRotation(const glm::vec3& NewValue);
    virtual void SetScale(const glm::vec3& NewValue);

    glm::vec3& GetPosition();
    glm::vec3& GetRotation();
    glm::vec3& GetScale();

private:

    Instance* CurrentInstance = nullptr;

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    friend class Instance;

};