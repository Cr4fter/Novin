#pragma once
#include "C:/Users/noah.forberich/Documents/Visual Studio 2017/Projects/Novin/PhysicsBullet/src/BulletDynamics/Dynamics/btRigidBody.h"
//#include <BulletDynamics/Dynamics/btRigidBody.h>
//#include "LinearMath/btMotionState.h"
#include <LinearMath/btMotionState.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
namespace NV
{
    namespace Physics
    {
        class RigidBody
        {
            btCollisionShape* m_Shape = nullptr;
            btScalar m_Mass = 0;
            bool m_IsDynamic = false;
            btVector3 m_LocalInteria;
            btMotionState* m_MotionState = nullptr;
            btRigidBody* m_BtRigidBody = nullptr;

            btTransform* m_Transform;

        public:
            RigidBody(int, btCollisionShape*, btVector3);
            btRigidBody* GetRigidBody();
            btMotionState* GetMotionState();

            void SetMass(float mass);
            void SetPosition(btVector3 newPos);
        };
    }
}
