#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformable
{
public:
    Transformable() noexcept;
    virtual ~Transformable();

    void setPosition(float x, float y, float z) noexcept;
    void setPosition(const glm::vec3& position) noexcept;

    void setAxisOfRotation(const glm::vec3& axis = glm::vec3(1.0f)) noexcept;
    void setRotation(float degrees)                                 noexcept;
    void rotate(float degrees)                                      noexcept;

    void setScale(float x, float y, float z) noexcept;
    void setScale(const glm::vec3& scale)    noexcept;
    void setScale(float scale)               noexcept;

    const glm::vec3& getPosition() const noexcept;
    const glm::vec3& getRotation() const noexcept;
    const glm::vec3& getScale()    const noexcept;

    const glm::mat4& getMatrix() const noexcept;

private:
    mutable glm::mat4 m_matrix;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_axisOfRotation;
    glm::vec3 m_scale;

    float m_angle;

    mutable bool m_matrixNeedUpdate;
};
#endif