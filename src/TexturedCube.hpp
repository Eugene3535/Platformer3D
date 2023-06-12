#ifndef TEXTURED_CUBE_HPP
#define TEXTURED_CUBE_HPP

#include <glad/glad.h>

#include "Defines.hpp"
#include "Transformable.hpp"
#include "Color.hpp"

#include <vector>

class TexturedCube:
    public Transformable
{
public:
    enum Face: std::size_t
    {
        FRONT,
        BACK,
        BOTTOM,
        TOP,
        LEFT,
        RIGHT,
        FACES_MAX
    };

public:
    TexturedCube() noexcept;
    TexturedCube(class Shader* pShader) noexcept;
    ~TexturedCube();

    void setShader(class Shader* pShader) noexcept;
    void setTexture(class Texture2D* pTexture) noexcept;
    void setTextureRect(const glm::ivec4& rect) noexcept;
    void setTextureRect(const glm::ivec4& rect, Face face) noexcept;
    void setColor(const Color& color) noexcept;

    bool create(const glm::vec3& minPt, const glm::vec3& maxPt, int usage = GL_STATIC_DRAW) noexcept;

    class Shader*    getShader() noexcept;
    class Texture2D* getTexture() noexcept;
    const glm::vec3& getBounds() const noexcept;

    void draw() noexcept;

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    class Shader*    m_pShader;
    class Texture2D* m_pTexture;

    GLuint m_vao;
    GLuint m_vbo;

	glm::vec3 m_bounds;
};

#endif