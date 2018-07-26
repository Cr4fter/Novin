#pragma once
#include "RigidBody.h"
#include "IComponent.h"
#include "PhysicsEngine.h"

namespace NV
{
    namespace SceneSystem
    {
        class RigidBodyComponent : public IComponent
        {
            Physics::RigidBody* m_Rigidbody = nullptr;
            Physics::PhysicsEngine* PhysEngine = nullptr;
            btMotionState* m_Mstate = nullptr;
        public:
            RigidBodyComponent(Physics::PhysicsEngine* PhysicsEngine);

            void SetMass(float mass);
            void Initialize(GameObject* HostObject) override;
            void Update() override;
            void Teardown() override;
        };
    }
}
