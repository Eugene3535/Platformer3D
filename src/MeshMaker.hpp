#ifndef MESH_MAKER_HPP
#define MESH_MAKER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
	glm::vec2 uv;
};

void MakeCubeMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const glm::vec3& minPt, const glm::vec3& maxPt, const glm::vec2* uv = nullptr);
void MakeRepeatedSurfaceMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, GLuint width, GLuint height);

#endif