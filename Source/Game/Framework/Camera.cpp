/**
 * @file Camera.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {
    
}

glm::mat4 Camera::GetViewMatrix() {
    glm::vec3 CameraPosition = GetPosition();
    glm::vec3 CameraForward = GetCameraForwardDirection();
    glm::vec3 CameraUp = GetCameraUpDirection();
    glm::mat4 View = glm::lookAt(CameraPosition, CameraPosition + CameraForward, CameraUp);
    return View;
}

glm::mat4 Camera::GetProjectionMatrix() {
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 720.0f / 720.0f, 0.1f, 1000.0f);
    return Projection;
}

glm::vec3 Camera::GetCameraUpDirection() {
    return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Camera::GetCameraForwardDirection() {
    glm::vec3 CurrentRotation = GetRotation();
    f32 Roll = CurrentRotation.x;
    f32 Pitch = CurrentRotation.y;
    f32 Yaw = CurrentRotation.z;

    glm::vec3 Direction = glm::vec3(0.0f);
    Direction.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    Direction.y = glm::sin(glm::radians(Pitch));
    Direction.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    Direction = glm::normalize(Direction);
    return Direction;
}

glm::vec3 Camera::GetCameraRightDirection() {
    return glm::normalize(glm::cross(GetCameraForwardDirection(), GetCameraUpDirection()));
}