/**
 * @file Camera.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Entity.h"

class Camera : public Entity
{
    using Super = Entity;
public:

    Camera();
    virtual ~Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    glm::vec3 GetCameraUpDirection();
    glm::vec3 GetCameraForwardDirection();
    glm::vec3 GetCameraRightDirection();

private:

};