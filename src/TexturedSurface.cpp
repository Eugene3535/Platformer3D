#include "TexturedSurface.hpp"
#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "Texture2D.hpp"
#include "MeshMaker.hpp"

TexturedSurface::TexturedSurface() noexcept:
    m_vao(0), m_vbo(0)
{
}

TexturedSurface::TexturedSurface(Shader* pShader) noexcept:
    Drawable(pShader), m_vao(0), m_vbo(0)
{
}

TexturedSurface::~TexturedSurface()
{
    if(m_vao)
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    } 
}

void TexturedSurface::setShader(Shader* pShader) noexcept
{
    m_pShader = pShader;
}

void TexturedSurface::setTexture(Texture2D* pTexture) noexcept
{
    m_pTexture = pTexture;
    m_pTexture->setRepeated(true);
}

void TexturedSurface::setTextureRect(const glm::ivec4& rect) noexcept
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

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    Vertex* pVertex = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    
    // for (std::size_t i = 0; i < FACES_MAX; ++i)
    // {
    //     pVertex[0].uv.x = left;
    //     pVertex[0].uv.y = bottom;

    //     pVertex[1].uv.x = right;
    //     pVertex[1].uv.y = bottom;

    //     pVertex[2].uv.x = right;
    //     pVertex[2].uv.y = top;

    //     pVertex[3].uv.x = left;
    //     pVertex[3].uv.y = top;     

    //     pVertex += 4;
    // }  

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TexturedSurface::setColor(const Color& color) noexcept
{
    m_pShader->bind();
    m_pShader->setUniform("inColor", color);
    m_pShader->unbind();
}

bool TexturedSurface::create(GLuint width, GLuint height, int usage) noexcept
{
    if(m_vao) return false;

    float vw = width + 1.0f;
    float vh = height + 1.0f;

    float half_w = width * 0.5f;
    float half_h = height * 0.5f;

    m_vertices.reserve((vw + 1) * (vh + 1));
    m_indices.reserve(width * height * 6);

    for (float i = 0; i < vh; i += 1.0f)
    {
        for (float j = 0; j < vw; j += 1.0f)
        {
            auto& vertex = m_vertices.emplace_back();

            vertex.position.x = j - half_w;
            vertex.position.z = i - half_h;
            vertex.uv.x = j;
            vertex.uv.y = i;
        }
    }

    for (GLuint i = 0; i < height; ++i)
    {
        for (GLuint j = 0; j < width; ++j)
        {
            GLuint pos = i * vw + j;

            m_indices.push_back(pos);
            m_indices.push_back(pos + 1);
            m_indices.push_back(pos + vw);

            m_indices.push_back(pos + 1);
            m_indices.push_back(pos + vw);
            m_indices.push_back(pos + vw + 1);
        }
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), usage);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

#ifdef DEBUG
    return !glGetError();
#endif

    return true;
}

Texture2D* TexturedSurface::getTexture() noexcept
{
    return m_pTexture;
}

void TexturedSurface::draw(RenderTarget* target)
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader) return;
#endif

    m_pTexture->bind(0);
    m_pShader->bind();

    m_pShader->setUniform("model", getMatrix());
    target->draw(GL_TRIANGLES, m_vao, m_indices.size(), m_indices.data());
      
    m_pTexture->unbind();
    m_pShader->unbind();
}