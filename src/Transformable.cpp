#include "Transformable.hpp"

Transformable::Transformable() noexcept:
    m_matrix(glm::identity<glm::mat4>()),
    m_position(),
    m_rotation(),
    m_axisOfRotation(1.0f),
    m_scale(1.0f),
    m_angle(0.0f)
{
}

Transformable::~Transformable()
{
}

void Transformable::setPosition(float x, float y, float z) noexcept
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    m_matrix = glm::translate(m_matrix, m_position);
}

void Transformable::setPosition(const glm::vec3& position) noexcept
{
    setPosition(position.x, position.y, position.z);
}

void Transformable::setAxisOfRotation(float dx, float dy, float dz) noexcept
{
    m_axisOfRotation = { dx, dy, dz };
}

void Transformable::setAxisOfRotation(const glm::vec3& axis) noexcept
{
    m_axisOfRotation = axis;
}

void Transformable::setRotation(float degrees) noexcept
{
    m_angle = glm::radians(degrees);

    if(m_axisOfRotation.x) m_rotation.x = m_angle;
    if(m_axisOfRotation.y) m_rotation.y = m_angle;
    if(m_axisOfRotation.z) m_rotation.z = m_angle;

    m_matrix = glm::rotate(m_matrix, m_angle, m_axisOfRotation);
}

void Transformable::rotate(float degrees) noexcept
{
    setRotation(m_angle + degrees);
}

void Transformable::setScale(float x, float y, float z) noexcept
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;

    m_matrix = glm::scale(m_matrix, m_scale);
}

void Transformable::setScale(const glm::vec3& scale) noexcept
{
    setScale(scale.x, scale.y, scale.z);
}

void Transformable::setScale(float scale) noexcept
{
    m_scale = glm::vec3(scale);

    m_matrixNeedUpdate = true;
}

const glm::vec3& Transformable::getPosition() const noexcept
{
    return m_position;
}

const glm::vec3& Transformable::getRotation() const noexcept
{
    return m_rotation;
}

const glm::vec3& Transformable::getScale() const noexcept
{
    return m_scale;
}

const glm::mat4& Transformable::getMatrix() const noexcept
{
    return m_matrix;
}