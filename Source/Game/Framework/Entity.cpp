/**
 * @file Entity.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::Setup() {
    
}

void Entity::Update(f32 DeltaTime) {

}

void Entity::Draw() {

}

void Entity::SetPosition(const glm::vec3& NewValue) {
    Position = NewValue;
}

void Entity::SetRotation(const glm::vec3& NewValue) {
    Rotation = NewValue;
}

void Entity::SetScale(const glm::vec3& NewValue) {
    Scale = NewValue;
}

glm::vec3& Entity::GetPosition() {
    return Position;
}

glm::vec3& Entity::GetRotation() {
    return Rotation;
}

glm::vec3& Entity::GetScale() {
    return Scale;
}

Instance* Entity::GetInstance() const {
    return CurrentInstance;
}