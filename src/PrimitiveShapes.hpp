#ifndef PRIMITIVE_SHAPES_HPP
#define PRIMITIVE_SHAPES_HPP

#include "Drawable.hpp"
#include "Transformable.hpp"
#include "VertexBuffer.hpp"
 
class TexturedCube:
    public Drawable,
    public Transformable
{
public:
    TexturedCube() noexcept;
    TexturedCube(class Shader* pShader) noexcept;
    ~TexturedCube();

    void setTexture(class Texture2D* pTexture) noexcept;
    void init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const glm::vec3& bounds) noexcept;

    Texture2D*       getTexture() noexcept;
    const glm::vec3& getBounds() const noexcept;

    void draw(class RenderTarget* target) override;

private:
    VertexBuffer m_buffer;
    Texture2D*   m_pTexture;
	glm::vec3    m_bounds;
};

class TexturedSurface:
	public Drawable,
    public Transformable
{
public:
	TexturedSurface() noexcept;
    TexturedSurface(class Shader* pShader) noexcept;
	~TexturedSurface();

    void setTexture(class Texture2D* pTexture) noexcept;
    void init(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const glm::vec3& bounds) noexcept;

    Texture2D*       getTexture() noexcept;
    const glm::vec3& getBounds() const noexcept;
    
    void draw(class RenderTarget* target) override;

private:
    VertexBuffer m_buffer;
    Texture2D*   m_pTexture;
	glm::vec3    m_bounds;
};

#endif