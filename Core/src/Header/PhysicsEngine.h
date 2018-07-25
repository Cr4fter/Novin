#pragma once
#include "RigidBody.h"
#include "btBulletDynamicsCommon.h"

namespace NV {
    namespace Threading {
        class ThreadPool;
    }
    namespace Core {
        class EngineState;
    }
    namespace Physics
    {
        class physics;
    }
}

namespace NV
{
    namespace Physics
    {
        enum CollisionShape
        {
            box
        };

        class PhysicsEngine
        {
            Core::EngineState* m_EngineState = nullptr;
            Threading::ThreadPool* m_ThreadPool = nullptr;

            btDefaultCollisionConfiguration* m_CollisionConfig = nullptr;
            btCollisionDispatcher* m_Dispatcher = nullptr;
            btBroadphaseInterface* m_overlappingPairCache = nullptr;
            btSequentialImpulseConstraintSolver* m_solver = nullptr;
            btDiscreteDynamicsWorld* m_DynamicsWorld = nullptr;

            btAlignedObjectArray<btCollisionShape*>* m_Collider = nullptr;

        public:

            void RegisterRigidbody(RigidBody&);

            void UnRegisterRigidbody(RigidBody&);

            void Initialize(Core::EngineState*, Threading::ThreadPool*);

            void Update(float DaltaTime);

            void Teardown();
        };
    }
}
