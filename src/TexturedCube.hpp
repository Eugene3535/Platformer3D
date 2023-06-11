#ifndef TEXTURED_CUBE_HPP
#define TEXTURED_CUBE_HPP

#include "Drawable.hpp"
#include "Transformable.hpp"
#include "VertexBuffer.hpp"
#include "Color.hpp"

class TexturedCube:
    public Drawable,
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

    void setTexture(class Texture2D* pTexture) noexcept;
    void setTextureRect(const glm::ivec4& rect) noexcept;
    void setTextureRect(const glm::ivec4& rect, Face face) noexcept;
    void setColor(const Color& color) noexcept;

    void init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const glm::vec3& bounds, int usage = GL_STATIC_DRAW) noexcept;

    Texture2D*       getTexture() noexcept;
    const glm::vec3& getBounds() const noexcept;

    void draw(class RenderTarget* target) override;

private:
    VertexBuffer m_buffer;
    Texture2D*   m_pTexture;
	glm::vec3    m_bounds;
};

#endif