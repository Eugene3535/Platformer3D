#include "RenderTarget.hpp"

RenderTarget::RenderTarget() noexcept
{
}

RenderTarget::~RenderTarget()
{
}

void RenderTarget::clear(const Color& color) noexcept
{
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void RenderTarget::draw(Drawable& object) noexcept
{
    object.draw(this);
}

void RenderTarget::draw(GLenum type, GLuint vao, GLuint count, const GLuint* indices) noexcept
{
    glBindVertexArray(vao);
    glDrawElements(type, count, GL_UNSIGNED_INT, indices);
    glBindVertexArray(0);
}