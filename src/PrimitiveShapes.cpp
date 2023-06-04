#include "PrimitiveShapes.hpp"
#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "Texture2D.hpp"
#include "MeshMaker.hpp"

//                                                TEXTURED CUBE
TexturedCube::TexturedCube() noexcept
{
}

TexturedCube::TexturedCube(class Shader* pShader) noexcept:
    Drawable(pShader)
{
}

TexturedCube::~TexturedCube()
{
}

void TexturedCube::setTexture(class Texture2D* pTexture) noexcept
{
    m_pTexture = pTexture;
}

void TexturedCube::setTextureRect(const glm::ivec4& rect, Face face) noexcept
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader || face >= FACES_MAX) return;
#endif

    const auto& texSize = m_pTexture->getSize();
    float tex_width  = static_cast<float>(texSize.x);
    float tex_height = static_cast<float>(texSize.y);

    float left   = static_cast<float>(rect.x) / tex_width;
    float top    = static_cast<float>(rect.y) / tex_height;
    float right  = static_cast<float>(rect.x + rect.z) / tex_width;
    float bottom = static_cast<float>(rect.y + rect.w) / tex_height;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer.vbo);
    Vertex* pVertex = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    pVertex += face * 4;

    pVertex[0].uv.x = left;
    pVertex[0].uv.y = top;

    pVertex[1].uv.x = right;
    pVertex[1].uv.y = top;

    pVertex[2].uv.x = right;
    pVertex[2].uv.y = bottom;

    pVertex[3].uv.x = left;
    pVertex[3].uv.y = bottom;

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void TexturedCube::draw(class RenderTarget* target)
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