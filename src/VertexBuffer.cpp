#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() noexcept:
    pIndices(nullptr),
    indexCount(0), 
    vao(0), 
    vbo(0)
{
}

VertexBuffer::~VertexBuffer()
{
    destroy();
}

bool VertexBuffer::create(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) noexcept
{
#ifdef DEBUG
    if(vao) destroy();
    if(vertices.empty()) return false; 
#endif    

    pIndices = indices.data();
    indexCount = indices.size();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

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

void VertexBuffer::destroy() noexcept
{
    if(vao)
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

        pIndices = nullptr;
        vao = vbo = indexCount = 0;
    } 
}