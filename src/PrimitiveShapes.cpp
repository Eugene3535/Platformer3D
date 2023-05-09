#include "PrimitiveShapes.hpp"
#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "Texture2D.hpp"
#include "MeshMaker.hpp"

TexturedCube::TexturedCube() noexcept
{
}

TexturedCube::TexturedCube(Shader* pShader) noexcept:
    Drawable(pShader)
{
}

TexturedCube::~TexturedCube()
{
}

void TexturedCube::setTexture(Texture2D* pTexture) noexcept
{
    m_pTexture = pTexture;
}

void TexturedCube::init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const glm::vec3& bounds) noexcept
{
    m_buffer.create(vertices, indices);
    m_bounds = bounds;
}

Texture2D* TexturedCube::getTexture() noexcept
{
    return m_pTexture;
}

const glm::vec3& TexturedCube::getBounds() const noexcept
{
    return m_bounds;
}

void TexturedCube::draw(RenderTarget* target)
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader) return;
#endif

    glBindVertexArray(m_buffer.vao);
    m_pTexture->bind(0);
    m_pShader->bind();

    m_pShader->setUniform("model", getMatrix());
    target->draw(GL_TRIANGLES, m_buffer.vao, m_buffer.indexCount, m_buffer.pIndices);
    
    glBindVertexArray(0);
    m_pTexture->unbind();
    m_pShader->unbind();
}

//                                                        TEXTURED SURFACE
TexturedSurface::TexturedSurface() noexcept
{
}

TexturedSurface::TexturedSurface(Shader* pShader) noexcept:
    Drawable(pShader)
{
}

TexturedSurface::~TexturedSurface()
{
}

void TexturedSurface::setTexture(Texture2D* pTexture) noexcept
{
    m_pTexture = pTexture;
}

void TexturedSurface::init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const glm::vec3& bounds) noexcept
{
    m_buffer.create(vertices, indices);
    m_bounds = bounds;
}

Texture2D* TexturedSurface::getTexture() noexcept
{
    return m_pTexture;
}

const glm::vec3& TexturedSurface::getBounds() const noexcept
{
    return m_bounds;
}

void TexturedSurface::draw(RenderTarget* target)
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader) return;
#endif

    glBindVertexArray(m_buffer.vao);
    m_pTexture->bind(0);
    m_pShader->bind();

    m_pShader->setUniform("model", getMatrix());
    target->draw(GL_TRIANGLES, m_buffer.vao, m_buffer.indexCount, m_buffer.pIndices);
    
    glBindVertexArray(0);
    m_pTexture->unbind();
    m_pShader->unbind();
}