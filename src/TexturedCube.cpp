#include "TexturedCube.hpp"
#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "Texture2D.hpp"
#include "MeshMaker.hpp"

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

void TexturedCube::setTextureRect(const glm::ivec4& rect) noexcept
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader) return;
#endif

    const auto& texSize = m_pTexture->getSize();
    float tex_width  = static_cast<float>(texSize.x);
    float tex_height = static_cast<float>(texSize.y);

    float left   = rect.x > 0 ? static_cast<float>(rect.x) / tex_width : 0.0f;
    float top    = rect.y > 0 ? static_cast<float>(rect.y) / tex_height : 0.0f;
    float right  = static_cast<float>(rect.x + rect.z) / tex_width;
    float bottom = static_cast<float>(rect.y + rect.w) / tex_height;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer.vbo);
    Vertex* pVertex = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    
    for (std::size_t i = 0; i < FACES_MAX; ++i)
    {
        pVertex[0].uv.x = left;
        pVertex[0].uv.y = bottom;

        pVertex[1].uv.x = right;
        pVertex[1].uv.y = bottom;

        pVertex[2].uv.x = right;
        pVertex[2].uv.y = top;

        pVertex[3].uv.x = left;
        pVertex[3].uv.y = top;     

        pVertex += 4;
    }  

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TexturedCube::setTextureRect(const glm::ivec4& rect, Face face) noexcept
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader || face >= FACES_MAX) return;
#endif

    const auto& texSize = m_pTexture->getSize();
    float tex_width  = static_cast<float>(texSize.x);
    float tex_height = static_cast<float>(texSize.y);

    float left   = rect.x > 0 ? static_cast<float>(rect.x) / tex_width : 0.0f;
    float top    = rect.y > 0 ? static_cast<float>(rect.y) / tex_height : 0.0f;
    float right  = static_cast<float>(rect.x + rect.z) / tex_width;
    float bottom = static_cast<float>(rect.y + rect.w) / tex_height;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer.vbo);
    Vertex* pVertex = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    pVertex += face * 4;

    pVertex[0].uv.x = left;
    pVertex[0].uv.y = bottom;

    pVertex[1].uv.x = right;
    pVertex[1].uv.y = bottom;

    pVertex[2].uv.x = right;
    pVertex[2].uv.y = top;

    pVertex[3].uv.x = left;
    pVertex[3].uv.y = top;    

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TexturedCube::setColor(const Color& color) noexcept
{
    m_pShader->bind();
    m_pShader->setUniform("inColor", color);
    m_pShader->unbind();
}

void TexturedCube::init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const glm::vec3& bounds, int usage) noexcept
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

    m_pTexture->bind(0);
    m_pShader->bind();

    m_pShader->setUniform("model", getMatrix());
    target->draw(GL_TRIANGLES, m_buffer.vao, m_buffer.indexCount, m_buffer.pIndices);
    
    m_pTexture->unbind();
    m_pShader->unbind();
}