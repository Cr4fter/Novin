#include "../Header/SceneManager.h"
#include <exception>
#include "Log.h"
#include "../Header/RigidBodyComponent.h"

void NV::SceneSystem::SceneManager::Initialize(Physics::PhysicsEngine* Physics)
{
    Debug::Log::LogMessage("Scene Manager Initialized!");
    m_ActiveScene = SetupScene();
}

void NV::SceneSystem::SceneManager::Update()
{
    if (m_ActiveScene == nullptr)
    {
        throw std::exception("No Active Scene");
    }
}

void NV::SceneSystem::SceneManager::Teardown()
{
}

NV::SceneSystem::Scene* NV::SceneSystem::SceneManager::SetupScene()
{
    Scene* scene = new Scene();
    scene->SoftInitialize();

    // -- Debug Scene Setup --
    GameObject* G1 = new GameObject();
    RigidBodyComponent* Rbody = new RigidBodyComponent();
    G1->AddComponent(Rbody);
    scene->AddSceneObject(G1);
    return scene;
}

void NV::SceneSystem::SceneManager::SwitchScene(Scene* scene)
{
}
