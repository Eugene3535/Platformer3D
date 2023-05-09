#include "Camera.hpp"

Camera::Camera() noexcept:
    m_viewMatrix(glm::identity<glm::mat4>()),
    m_position(glm::vec3(0.0f)),
    m_target(glm::vec3(0.0f)),
    Up(glm::vec3(0.0f, 1.0f, 0.0f)),
    Right(glm::vec3(0.0f)),
    m_velocity(5),
    m_pitch(0.0f),
    m_yaw(0.0f),
    m_viewNeedUpdate(true)
{
    updateCameraVectors();
}

void Camera::setPosition(float x, float y, float z) noexcept
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    m_viewNeedUpdate = true;
}

void Camera::setPosition(const glm::vec3& position) noexcept
{
    m_position = position;

    m_viewNeedUpdate = true;
}

void Camera::move(Direction dir, float deltaTime) noexcept
{
    float velocity = m_velocity * deltaTime;

    switch (dir)
    {
    case FORWARD:
        m_position += m_target * velocity;
        break;

    case BACKWARD:
        m_position -= m_target * velocity;
        break;

    case LEFT:
        m_position -= Right * velocity;
        break;

    case RIGHT:
        m_position += Right * velocity;
        break;
    
    default:
        break;
    }

    m_viewNeedUpdate = true;
}

void Camera::rotate(float dx, float dy) noexcept
{
    m_yaw += dx;
    m_pitch += dy;

    m_pitch = (m_pitch > 89.0f) ? 89.0f : (m_pitch < -89.0f) ? -89.0f : m_pitch; 

    updateCameraVectors();

    m_viewNeedUpdate = true;
}

const glm::vec3& Camera::getPosition() const noexcept
{
    return m_position;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    if (m_viewNeedUpdate)
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_target, Up);
        m_viewNeedUpdate = false;
    }

    return m_viewMatrix;
}

void Camera::updateCameraVectors() noexcept
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_target = glm::normalize(front);

    Right = glm::normalize(glm::cross(m_target, glm::vec3(0.0f, 1.0f, 0.0f)));
    Up = glm::normalize(glm::cross(Right, m_target));
}