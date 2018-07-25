#pragma once
#include "Scene.h"
#include "PhysicsEngine.h"

namespace NV
{
    namespace SceneSystem
    {
        class SceneManager
        {
            Scene* m_ActiveScene = nullptr;

        public:
            void Initialize(Physics::PhysicsEngine*);
            void Update();
            void Teardown();

            Scene* SetupScene();
            void SwitchScene(Scene* scene);
        };
    }
}
