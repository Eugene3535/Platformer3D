#ifndef TEXTURED_SURFACE_HPP
#define TEXTURED_SURFACE_HPP

#include "Drawable.hpp"
#include "Transformable.hpp"
#include "VertexBuffer.hpp"
#include "Color.hpp"

#include <vector>

class TexturedSurface:
	public Drawable,
    public Transformable
{
public:
	TexturedSurface() noexcept;
    TexturedSurface(class Shader* pShader) noexcept;
	~TexturedSurface();

    void setShader(class Shader* pShader) noexcept;
    void setTexture(class Texture2D* pTexture) noexcept;
    void setTextureRect(const glm::ivec4& rect) noexcept;
    void setColor(const Color& color) noexcept;

    bool create(GLuint width, GLuint height, int usage = GL_STATIC_DRAW) noexcept;

    Texture2D* getTexture() noexcept;
    
    void draw(class RenderTarget* target) override;

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    class Texture2D* m_pTexture;

    GLuint m_vao;
    GLuint m_vbo;
};

#endif