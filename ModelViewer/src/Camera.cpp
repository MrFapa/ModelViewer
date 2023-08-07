#include "Camera.h"

Camera::Camera(float aspectRatio)
    : m_Position({ 0, 0, -3 }), m_Target({ 0, 0, 0 })
{
    m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    UpdateVectors();
}

void Camera::Move(float yaw, float pitch)
{
    if (yaw == 0.0f && pitch == 0.0f)
        return;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    rotation = glm::rotate(rotation, pitch, m_Right);
    m_Position = glm::vec3(rotation * glm::vec4(m_Position - m_Target, 1.0f)) + m_Target;

    UpdateVectors();
    
}

void Camera::UpdateVectors()
{
    m_Forward = glm::normalize(m_Target - m_Position);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Right = glm::normalize(glm::cross(m_Forward, worldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}

glm::mat4 Camera::GetProjViewMatrix()
{
    return m_ProjectionMatrix * glm::lookAt(m_Position, m_Target, m_Up);
}
