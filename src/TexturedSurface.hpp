#ifndef TEXTURED_SURFACE_HPP
#define TEXTURED_SURFACE_HPP

#include <glad/glad.h>

#include "Defines.hpp"
#include "Transformable.hpp"
#include "Color.hpp"

#include <vector>

class TexturedSurface:
    public Transformable
{
public:
	TexturedSurface() noexcept;
    TexturedSurface(class Shader* pShader) noexcept;
	~TexturedSurface();

    void setShader(class Shader* pShader) noexcept;
    void setTexture(class Texture2D* pTexture) noexcept;
    void setColor(const Color& color) noexcept;

    bool create(GLuint width, GLuint height, int usage = GL_STATIC_DRAW) noexcept;

    class Shader*    getShader() noexcept;
    class Texture2D* getTexture() noexcept;
    
    void draw() noexcept;

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    class Shader*    m_pShader;
    class Texture2D* m_pTexture;

    GLuint m_vao;
    GLuint m_vbo;
};

#endif