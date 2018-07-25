#pragma once
#include "GameObject.h"

namespace NV
{
    namespace SceneSystem
    {
        class Scene
        {
            bool m_IsActiveScene = false;
            std::list<GameObject*> m_SceneObjects;
        public:
            void SoftInitialize();
            void HardInitialize();
            void Update();
            void Teardown();

            void AddSceneObject(GameObject*);

            void SetAceneActive();
            void SetInAceneActive();
        };
    }
}
