#include "Engine.h"
#include "IRendering.h"
#include "iniContainer.h"
#include "EngineState.h"
#include "../Header/SceneManager.h"
#include <ThreadPool.h>
#include "Log.h"
#include <cstdio>
#include <chrono>
#include <thread>
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;
typedef NV::IRendering::IRenderer*(*GetRenderingInstance)();

NV::Core::Engine::~Engine()
{
    delete m_EngineState;
}

void NV::Core::Engine::Init(const std::string& ProjectPath)
{
    Debug::Log* instance = new Debug::Log;
    instance->SetUpLogInstance();

    Debug::Log::LogMessage("Engine Init");

    std::string ProjectPathComplete = ProjectPath;

    if (ProjectPathComplete[ProjectPathComplete.length() - 1] != '\\')
    {
        ProjectPathComplete += "\\";
    }

    m_EngineState = new EngineState(ProjectPathComplete);

    m_ThreadPool = new Threading::ThreadPool();
    m_ThreadPool->Init(m_EngineState);

    link_Setup_renderer();
    m_Renderer->Init();

    m_Physics = new Physics::PhysicsEngine();
    m_Physics->Initialize(m_EngineState, m_ThreadPool);

    m_Audio = new Audio::Audio();
    m_Audio->Initialize(m_EngineState, m_ThreadPool);

    m_Scene = new SceneSystem::SceneManager();
    m_Scene->Initialize(m_Physics);

    m_Initialized = true;
}

void NV::Core::Engine::Run()
{
    if (!m_Initialized)
    {
        throw std::exception("Engine Was not Initialized!");
    }
    Debug::Log::LogMessage("Engine Run");

    while (m_EngineState->GetIsRunning())
    {
        auto frameStart = Clock::now();
        Debug::Log::HandleUpdate();
        m_Physics->Update(DeltaTime);
        m_Scene->Update();

        //TODO Update Engine Systems(PhysicsEngine, Audio)
        float ElapsedTime = (Clock::now() - frameStart).count() / 1000000.0f;
        if (ElapsedTime < 16)
        {
            float sleepingDif = 16.0f - ElapsedTime;
            //printf("Frame Took %f miliseconds! Sleeping for %f ms\n", ElapsedTime, sleepingDif);
            std::chrono::duration<float, std::milli> tmp(sleepingDif);
            std::this_thread::sleep_for(tmp);
        }
        DeltaTime = (Clock::now() - frameStart).count() / 1000000.0f;
    }
}

void NV::Core::Engine::Teardown()
{
    if (!m_Initialized)
    {
        throw std::exception("Engine Was not Initialized!");
    }
    printf("Engine Teardown\n");

    m_Scene->Teardown();
    delete m_Scene;

    //TODO Teardown everything else in reverse order!
}

void NV::Core::Engine::link_Setup_renderer()
{
    hGetProcIDDLL = LoadLibrary(L"Renderer.dll");

    if (hGetProcIDDLL == nullptr) {
        throw std::exception("cannot locate Renderer.dll");
    }

    const GetRenderingInstance GetRenderer = reinterpret_cast<GetRenderingInstance>(GetProcAddress(hGetProcIDDLL, "GetRenderer"));

    m_Renderer = GetRenderer();
}
