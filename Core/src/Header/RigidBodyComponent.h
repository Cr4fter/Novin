#pragma once
#include "RigidBody.h"
#include "IComponent.h"

namespace NV
{
    namespace SceneSystem
    {
        class RigidBodyComponent : public IComponent
        {
            Physics::RigidBody* m_Rigidbody = nullptr;
        public:
            void Initialize(GameObject* HostObject) override;
            void Update() override;
            void Teardown() override;
        };
    }
}
