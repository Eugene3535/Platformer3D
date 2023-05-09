#ifndef RENDER_TARGET_HPP
#define RENDER_TARGET_HPP

#include "Drawable.hpp"
#include "Color.hpp"

class RenderTarget final
{
public:
    RenderTarget() noexcept;
    ~RenderTarget();

    void clear(const Color& color = Color::Black) noexcept;
    void draw(Drawable& object) noexcept;
    void draw(GLenum type, GLuint vao, GLuint count, const GLuint* indices) noexcept;
};


#endif