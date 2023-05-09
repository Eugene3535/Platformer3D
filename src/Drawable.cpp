#include "Drawable.hpp"

#include "Shader.hpp"

Drawable::Drawable():
    m_pShader(nullptr)
{
}

Drawable::Drawable(Shader* pShader):
    m_pShader(pShader)
{
}

Drawable::~Drawable()
{
}

void Drawable::setShader(Shader* pShader)
{
    m_pShader = pShader;
}

Shader* Drawable::getShader()
{
    return m_pShader;
}