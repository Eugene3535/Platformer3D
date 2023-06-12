#include "TexturedCube.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

TexturedCube::TexturedCube() noexcept:
    m_pShader(nullptr), 
    m_pTexture(nullptr),
    m_vao(0), 
    m_vbo(0)
{
}

TexturedCube::TexturedCube(class Shader* pShader) noexcept:
    m_pShader(pShader), 
    m_pTexture(nullptr),
    m_vao(0), 
    m_vbo(0)
{
}

TexturedCube::~TexturedCube()
{
    if(m_vao)
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    } 
}

void TexturedCube::setShader(Shader* pShader) noexcept
{
    m_pShader = pShader;
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

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
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

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
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

bool TexturedCube::create(const glm::vec3& minPt, const glm::vec3& maxPt, int usage) noexcept
{
    const static glm::vec2 cubeUV[] = // one texture on all faces by default
    {
        { 0.0f, 1.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 0.0f }
    };

    if(m_vao) return false;

    m_vertices =
    {
        //      Front
        {{minPt.x, minPt.y, maxPt.z}, glm::vec3(), cubeUV[0]},
        {{maxPt.x, minPt.y, maxPt.z}, glm::vec3(), cubeUV[1]},
        {{maxPt.x, maxPt.y, maxPt.z}, glm::vec3(), cubeUV[2]},
        {{minPt.x, maxPt.y, maxPt.z}, glm::vec3(), cubeUV[3]},
        //      Back
        {{maxPt.x, minPt.y, minPt.z}, glm::vec3(), cubeUV[0]},
        {{minPt.x, minPt.y, minPt.z}, glm::vec3(), cubeUV[1]},
        {{minPt.x, maxPt.y, minPt.z}, glm::vec3(), cubeUV[2]},
        {{maxPt.x, maxPt.y, minPt.z}, glm::vec3(), cubeUV[3]},
        //      Bottom
        {{minPt.x, minPt.y, minPt.z}, glm::vec3(), cubeUV[0]},
        {{maxPt.x, minPt.y, minPt.z}, glm::vec3(), cubeUV[1]},
        {{maxPt.x, minPt.y, maxPt.z}, glm::vec3(), cubeUV[2]},
        {{minPt.x, minPt.y, maxPt.z}, glm::vec3(), cubeUV[3]},
        //      Top
        {{minPt.x, maxPt.y, maxPt.z}, glm::vec3(), cubeUV[0]},
        {{maxPt.x, maxPt.y, maxPt.z}, glm::vec3(), cubeUV[1]},
        {{maxPt.x, maxPt.y, minPt.z}, glm::vec3(), cubeUV[2]},
        {{minPt.x, maxPt.y, minPt.z}, glm::vec3(), cubeUV[3]},
        //      Left
        {{minPt.x, minPt.y, minPt.z}, glm::vec3(), cubeUV[0]},
        {{minPt.x, minPt.y, maxPt.z}, glm::vec3(), cubeUV[1]},
        {{minPt.x, maxPt.y, maxPt.z}, glm::vec3(), cubeUV[2]},
        {{minPt.x, maxPt.y, minPt.z}, glm::vec3(), cubeUV[3]},
        //      Right
        {{maxPt.x, minPt.y, maxPt.z}, glm::vec3(), cubeUV[0]},
        {{maxPt.x, minPt.y, minPt.z}, glm::vec3(), cubeUV[1]},
        {{maxPt.x, maxPt.y, minPt.z}, glm::vec3(), cubeUV[2]},
        {{maxPt.x, maxPt.y, maxPt.z}, glm::vec3(), cubeUV[3]}
    };

    m_indices.resize(36);

    for (GLuint i = 0, n = 0; i < 36; i += 6, n += 4)
    {
        GLuint* pIndex = &m_indices[i];

        pIndex[0] = n;
        pIndex[1] = n + 1;
        pIndex[2] = n + 3;
        pIndex[3] = n + 1;
        pIndex[4] = n + 2;
        pIndex[5] = n + 3;
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

Shader* TexturedCube::getShader() noexcept
{
    return m_pShader;
}

Texture2D* TexturedCube::getTexture() noexcept
{
    return m_pTexture;
}

const glm::vec3& TexturedCube::getBounds() const noexcept
{
    return m_bounds;
}

void TexturedCube::draw() noexcept
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