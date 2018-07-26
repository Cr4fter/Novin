#pragma once
namespace NV
{
    namespace SceneSystem
    {
        class GameObject;

        class IComponent
        {
        protected:
            GameObject* m_HostObject = nullptr;
        public:
            virtual ~IComponent() = default;
            virtual void Initialize(GameObject* HostObject) = 0;
            virtual void Update() = 0;
            virtual void Teardown() = 0;
        };
    }
}