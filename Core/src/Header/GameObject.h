#pragma once
#include <list>
#include "IComponent.h"
#include "TransformComponent.h"

namespace NV
{
    namespace SceneSystem
    {
        class GameObject
        {
            TransformComponent* m_Transform = nullptr;
            std::list<IComponent*> m_Components;
        public:
            void Initialize();
            void Update();
            void Teardown();

            void AddComponent(IComponent* component);
        };
    }
}
