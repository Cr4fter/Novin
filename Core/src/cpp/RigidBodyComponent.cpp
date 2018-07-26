#include "../Header/ComponentRigidBody.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include <iostream>

void NV::SceneSystem::RigidBodyComponent::SetMass(float mass)
{
    m_Rigidbody->SetMass(mass);
}

void NV::SceneSystem::RigidBodyComponent::Initialize(GameObject* gm)
{
    m_HostObject = gm;
    btCollisionShape* shape = new btBoxShape(btVector3(1, 1, 1));
    m_Rigidbody = new Physics::RigidBody(1, shape, btVector3(0, 0, 0));
    PhysEngine->RegisterRigidbody(*m_Rigidbody);
    m_Mstate = m_Rigidbody->GetMotionState();
}

NV::SceneSystem::RigidBodyComponent::RigidBodyComponent(Physics::PhysicsEngine * PhysicsEngine)
{
    PhysEngine = PhysicsEngine;
}

void NV::SceneSystem::RigidBodyComponent::Update()
{
    btTransform tans;
    m_Mstate->getWorldTransform(tans);
    printf("posy:%f %f %f\n", tans.getOrigin().getZ(), tans.getOrigin().getY(), tans.getOrigin().getZ());
}

void NV::SceneSystem::RigidBodyComponent::Teardown()
{
    PhysEngine->UnRegisterRigidbody(*m_Rigidbody);
    delete m_Rigidbody;
}
