#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    enum Direction: int 
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

public:
    Camera() noexcept;

    void setPosition(float x, float y, float z) noexcept;
    void setPosition(const glm::vec3& position) noexcept;

    void move(Direction dir, float dt) noexcept;
    void rotate(float dx, float dy) noexcept;

    const glm::vec3& getPosition() const noexcept;
    const glm::mat4& getViewMatrix() const noexcept;

private:
    void updateCameraVectors() noexcept;

private:
    mutable glm::mat4 m_viewMatrix;

    glm::vec3 m_position;
    glm::vec3 m_target;

    glm::vec3 Up;
    glm::vec3 Right;

    float m_pitch;
    float m_yaw;

    float m_velocity;

    mutable bool m_viewNeedUpdate;
};

#endif