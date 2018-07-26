#pragma once
#include <list>
#include "IComponent.h"
#include "ComponentTransform.h"

namespace NV
{
    namespace SceneSystem
    {
        class GameObject
        {
            TransformComponent* m_Transform = nullptr;
            std::list<IComponent*> m_Components;
            std::string m_Name;
        public:
            void Initialize();
            void Update();
            void Teardown();

            void AddComponent(IComponent* component);
            std::string GetName();
        };
    }
}
