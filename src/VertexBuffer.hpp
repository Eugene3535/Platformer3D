#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "MeshMaker.hpp"

class VertexBuffer final
{
public:
    VertexBuffer() noexcept;
    VertexBuffer(const VertexBuffer& buffer) = delete;
    VertexBuffer(const VertexBuffer&& buffer) = delete;
    VertexBuffer& operator =(const VertexBuffer& buffer) = delete;
    VertexBuffer& operator =(const VertexBuffer&& buffer) = delete;
    ~VertexBuffer();

    bool create(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, int usage = GL_STATIC_DRAW) noexcept;
    void destroy() noexcept;

public:
    const GLuint* pIndices;
    GLuint        indexCount;
    GLuint        vao;
    GLuint        vbo;
};

#endif