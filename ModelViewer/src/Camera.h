#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float aspectRatio);

    void Move(float yaw, float pitch);

    void SetPosition(const glm::vec3& position) { m_Position = position; }
    glm::vec3 GetPosition() const { return m_Position; }
    glm::mat4 GetProjViewMatrix();
    
private:
    glm::vec3 m_Position;
    glm::vec3 m_Target;
    glm::vec3 m_Forward;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::mat4 m_ProjectionMatrix;

private:
    void UpdateVectors();
};