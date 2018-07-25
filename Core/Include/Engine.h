#pragma once
#include <string>
#include "../src/Header/PhysicsEngine.h"
#include "../src/Header/Audio.h"

namespace NV {
    namespace SceneSystem {
        class SceneManager;
    }

    namespace IRendering {
        class IRenderer;
    }
    namespace Core
    {
        class EngineState;
    }
    namespace Threading
    {
        class ThreadPool;
    }
}

#if _WIN64
#include <windows.h>
#endif

namespace NV
{
    namespace Core
    {
        class Engine
        {
        public:
            ~Engine();

            void Init(const std::string&);
            void Run();
            void Teardown();
        private:
            HINSTANCE hGetProcIDDLL = nullptr;
            bool m_Initialized = false;

            EngineState* m_EngineState = nullptr;
            IRendering::IRenderer* m_Renderer = nullptr;
            Threading::ThreadPool* m_ThreadPool = nullptr;
            Physics::PhysicsEngine* m_Physics = nullptr;
            Audio::Audio* m_Audio = nullptr;

            SceneSystem::SceneManager* m_Scene = nullptr;

            void link_Setup_renderer();
        };
    }
}
