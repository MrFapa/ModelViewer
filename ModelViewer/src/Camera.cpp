#include "Camera.h"

#include <ios>

Camera::Camera()
	: m_Position({0, 0, -3}), m_Target({0, 0, 1}), m_NearPlane(-1), m_FarPlane(1), m_IsPerspective(false)
{
    UpdateVectors();
}

void Camera::Move(float yaw, float pitch)
{
	
}

void Camera::UpdateVectors()
{
	m_Forward = glm::normalize(m_Target - m_Position);

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Right = glm::normalize(glm::cross(m_Forward, worldUp));

	m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}

glm::mat4 Camera::GetViewMatrix()
{
	UpdateVectors();
	return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

