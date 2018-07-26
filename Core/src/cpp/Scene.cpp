#include "../Header/Scene.h"

void NV::SceneSystem::Scene::SoftInitialize()
{
}

void NV::SceneSystem::Scene::HardInitialize()
{
    for (auto* object : m_SceneObjects)
    {
        object->Initialize();
    }
}

void NV::SceneSystem::Scene::Update()
{
    for (auto* object : m_SceneObjects)
    {
        object->Update();
    }
}

void NV::SceneSystem::Scene::Teardown()
{
    for (auto* object : m_SceneObjects)
    {
        object->Teardown();
    }
}

void NV::SceneSystem::Scene::AddSceneObject(GameObject* SceneObject)
{
    m_SceneObjects.push_back(SceneObject);
}

void NV::SceneSystem::Scene::SetAceneActive()
{
}

void NV::SceneSystem::Scene::SetInAceneActive()
{
}
