#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <glad/glad.h>

class Drawable
{
public:
    Drawable();
    Drawable(class Shader* pShade);
    virtual ~Drawable();

    void setShader(class Shader* pShader);
    class Shader* getShader();

protected:
    virtual void draw(class RenderTarget* target) = 0;

protected:
    class Shader* m_pShader;

protected:
    friend class RenderTarget;
};

#endif