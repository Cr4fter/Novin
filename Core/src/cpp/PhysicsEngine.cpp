#include "../Header/PhysicsEngine.h"
#include <cstdio>
#include "ThreadPool.h"

void NV::Physics::PhysicsEngine::RegisterRigidbody(RigidBody& rbody)
{
    m_DynamicsWorld->addRigidBody(rbody.GetRigidBody());
}

void NV::Physics::PhysicsEngine::UnRegisterRigidbody(RigidBody& rbody)
{
    m_DynamicsWorld->removeRigidBody(rbody.GetRigidBody());
}

void NV::Physics::PhysicsEngine::Initialize(Core::EngineState* engineState, Threading::ThreadPool* tpool)
{
    m_EngineState = engineState;
    m_ThreadPool = tpool;
    printf("PhysicsEngine Initialized!\n");

    // Setup PhysicsEngine World
    m_CollisionConfig = new btDefaultCollisionConfiguration();
    m_Dispatcher = new btCollisionDispatcher(m_CollisionConfig);

    m_overlappingPairCache = new btDbvtBroadphase();

    m_solver = new btSequentialImpulseConstraintSolver();
    m_DynamicsWorld = new btDiscreteDynamicsWorld(m_Dispatcher, m_overlappingPairCache, m_solver, m_CollisionConfig);

    m_DynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

    m_Collider = new btAlignedObjectArray<btCollisionShape*>();
}

void NV::Physics::PhysicsEngine::Update(float DaltaTime)
{
    m_DynamicsWorld->stepSimulation(DaltaTime);
}

void NV::Physics::PhysicsEngine::Teardown()
{

    delete m_Collider;

    delete m_DynamicsWorld;
    delete m_solver;
    delete m_overlappingPairCache;
    delete m_Dispatcher;
    delete m_CollisionConfig;
}
