#pragma once
#include "IComponent.h"
#include "glm/gtc/quaternion.hpp"
namespace NV
{
    namespace SceneSystem
    {
        class TransformComponent : public IComponent
        {
            glm::vec3 m_Position = glm::vec3(0, 0, 0);
            glm::quat m_Rotation = glm::quat(glm::vec3(0, 0, 0));
            glm::vec3 m_Scale = glm::vec3(1, 1, 1);

        public:
            void Initialize(GameObject*) override;
            void Update() override;
            void Teardown() override;

            const glm::vec3 GetPosition() const;
            const glm::quat GetRotationQuat() const;
            const glm::vec3 GetRotationEuler() const;
            const glm::vec3 GetScale() const;
        };
    }
}
