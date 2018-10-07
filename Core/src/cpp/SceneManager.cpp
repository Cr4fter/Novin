#include "../Header/SceneManager.h"
#include <exception>
#include "../Header/ComponentRigidBody.h"
#include "../Header/ComponentLuaScript.h"
#include "Log.h"

void NV::SceneSystem::SceneManager::Initialize(Physics::PhysicsEngine* _PhysicsEngine)
{
    m_PhysicsEngine = _PhysicsEngine;
    m_ActiveScene = SetupScene();
    Debug::Log::LogMessage("Scene manager init");
}

void NV::SceneSystem::SceneManager::Update()
{
    if (m_ActiveScene == nullptr)
    {
        throw std::exception("No Active Scene");
    }

    m_ActiveScene->Update();
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
    G1->Initialize();
    Scripting::LuaScriptingComponent* Script = new Scripting::LuaScriptingComponent();
    G1->AddComponent(Script);
    scene->AddSceneObject(G1);

    //GameObject* G2 = new GameObject();
    //G2->Initialize();
    //RigidBodyComponent* Rbody2 = new RigidBodyComponent(m_PhysicsEngine);
    //G2->AddComponent(Rbody2);
    //Rbody2->SetMass(0);
    //scene->AddSceneObject(G2);

    return scene;
}

void NV::SceneSystem::SceneManager::SwitchScene(Scene* scene)
{
}
