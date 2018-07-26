#include "../Header/ComponentTransform.h"
#include <exception>
#include "iostream"

void NV::SceneSystem::TransformComponent::Initialize(GameObject* HostObject)
{
    m_HostObject = HostObject;
}

void NV::SceneSystem::TransformComponent::Update()
{
}

void NV::SceneSystem::TransformComponent::Teardown()
{
}

const glm::vec3 NV::SceneSystem::TransformComponent::GetPosition() const
{
    return m_Position;
}

const glm::quat NV::SceneSystem::TransformComponent::GetRotationQuat() const
{
    return m_Rotation;
}

const glm::vec3 NV::SceneSystem::TransformComponent::GetRotationEuler() const
{
    throw std::exception("Function is not implemented jet! please use the quaternion!");
}

const glm::vec3 NV::SceneSystem::TransformComponent::GetScale() const
{
    return m_Scale;
}
