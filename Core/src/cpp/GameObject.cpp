#include "../Header/GameObject.h"

void NV::SceneSystem::GameObject::Initialize()
{
    m_Transform = new TransformComponent();
    m_Transform->Initialize(this);
}

void NV::SceneSystem::GameObject::Update()
{
    m_Transform->Update();
    for(auto* comp : m_Components)
    {
        comp->Update();
    }
}

void NV::SceneSystem::GameObject::Teardown()
{
    for (auto* comp : m_Components)
    {
        comp->Teardown();
    }
    m_Transform->Teardown();
}

void NV::SceneSystem::GameObject::AddComponent(IComponent* component)
{
    m_Components.push_back(component);
    component->Initialize(this);
}
std::string NV::SceneSystem::GameObject::GetName()
{
    return m_Name;
}

NV::SceneSystem::TransformComponent* NV::SceneSystem::GameObject::GetTransform()
{
    return m_Transform;
}
