#include "../Header/RigidBodyComponent.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"

void NV::SceneSystem::RigidBodyComponent::Initialize(GameObject* gm)
{
    m_HostObject = gm;
    btCollisionShape* shape = new btBoxShape(btVector3(1, 1, 1));
    m_Rigidbody = new Physics::RigidBody(1, shape, btVector3(0, 0, 0));
}

void NV::SceneSystem::RigidBodyComponent::Update()
{
}

void NV::SceneSystem::RigidBodyComponent::Teardown()
{
    delete m_Rigidbody;
}
