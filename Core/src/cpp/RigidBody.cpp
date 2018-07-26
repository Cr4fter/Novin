#include "RigidBody.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btDefaultMotionState.h"

btRigidBody* NV::Physics::RigidBody::GetRigidBody()
{
    return m_BtRigidBody;
}

btMotionState * NV::Physics::RigidBody::GetMotionState()
{
    return m_MotionState;
}

void NV::Physics::RigidBody::SetMass(float mass)
{
    m_BtRigidBody->setMassProps(mass, m_LocalInteria);
}

void NV::Physics::RigidBody::SetPosition(btVector3 newPos)
{
    //TODO Update Rigidbody Position in PhysicsWorld
}

NV::Physics::RigidBody::RigidBody(int mass, btCollisionShape* shape, btVector3 Origin)
{
    m_Shape = shape;

    m_Mass = mass;
    if (mass != 0)
    {
        shape->calculateLocalInertia(mass, m_LocalInteria);
        m_IsDynamic = true;
    }
    m_Transform = new btTransform;
    m_Transform->setIdentity();
    m_Transform->setOrigin(Origin);

    m_MotionState = new btDefaultMotionState(*m_Transform);
    const btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_MotionState, m_Shape, m_LocalInteria);
    m_BtRigidBody = new btRigidBody(rbInfo);
}
