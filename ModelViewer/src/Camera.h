#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();

    void Move(float yaw, float pitch);

    void SetPosition(const glm::vec3& position) { m_Position = position; }
    void SetTarget(const glm::vec3& target) { m_Target = target; }
    //void setNearPlane(float nearPlane) { m_NearPlane = nearPlane; }
    //void setFarPlane(float farPlane) { m_FarPlane = farPlane; }

    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetTarget() const { return m_Target; }
    glm::vec3 GetForward() const { return m_Forward; }
    glm::vec3 GetUp() const { return m_Up; }
    glm::vec3 GetRight() const { return m_Right; }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Target;
    glm::vec3 m_Forward;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    //float m_NearPlane;
    //float m_FarPlane;
    //bool m_IsPerspective;

    //glm::mat4 m_ViewMatrix;

private:

    void UpdateVectors();
};