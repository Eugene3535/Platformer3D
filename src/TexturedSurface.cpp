#include "TexturedSurface.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

TexturedSurface::TexturedSurface() noexcept:
    m_pShader(nullptr), 
    m_pTexture(nullptr),
    m_vao(0), 
    m_vbo(0)
{
}

TexturedSurface::TexturedSurface(Shader* pShader) noexcept:
    m_pShader(pShader), 
    m_pTexture(nullptr),
    m_vao(0), 
    m_vbo(0)
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

    m_vertices.reserve((vw + 1) * (vh + 1));
    m_indices.reserve(width * height * 6);

    for (float i = 0; i < vh; i += 1.0f)
    {
        for (float j = 0; j < vw; j += 1.0f)
        {
            auto& vertex = m_vertices.emplace_back();

            vertex.position.x = j;
            vertex.position.z = i;
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

Shader* TexturedSurface::getShader() noexcept
{
    return m_pShader;
}

Texture2D* TexturedSurface::getTexture() noexcept
{
    return m_pTexture;
}

void TexturedSurface::draw() noexcept
{
#ifdef DEBUG
    if( ! m_pTexture || ! m_pShader) return;
#endif

    glBindVertexArray(m_vao);
    m_pTexture->bind(0);
    m_pShader->bind();

    m_pShader->setUniform("model", getMatrix());
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, m_indices.data());

    glBindVertexArray(0);     
    m_pTexture->unbind();
    m_pShader->unbind();
}