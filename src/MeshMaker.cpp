#include "MeshMaker.hpp"

void MakeCubeMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const glm::vec3& minPt, const glm::vec3& maxPt)
{
    vertices = 
    {
//      Front
        {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), { 0.0f, 0.0f }},
        {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), { 1.0f, 0.0f }},
        {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), { 1.0f, 1.0f }},
        {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), { 0.0f, 1.0f }},
//      Back
        {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), { 0.0f, 0.0f }},
        {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), { 1.0f, 0.0f }},
        {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), { 1.0f, 1.0f }},
        {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), { 0.0f, 1.0f }},
//      Bottom
        {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), { 0.0f, 0.0f }},
        {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), { 1.0f, 0.0f }},
        {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), { 1.0f, 1.0f }},
        {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), { 0.0f, 1.0f }},
//      Top
        {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), { 0.0f, 0.0f }},
        {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), { 1.0f, 0.0f }},
        {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), { 1.0f, 1.0f }},
        {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), { 0.0f, 1.0f }},
//      Left
        {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), { 0.0f, 0.0f }},
        {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), { 1.0f, 0.0f }},
        {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), { 1.0f, 1.0f }},
        {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), { 0.0f, 1.0f }},
//      Right
        {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), { 0.0f, 0.0f }},
        {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), { 1.0f, 0.0f }},
        {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), { 1.0f, 1.0f }},
        {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), { 0.0f, 1.0f }}
    };

    indices.resize(36);

    for (GLuint i = 0, n = 0; i < 36; i += 6, n += 4)
    {
        GLuint* pIndex = &indices[i];

        pIndex[0] = n;
        pIndex[1] = n + 1;
        pIndex[2] = n + 3;
        pIndex[3] = n + 1;
        pIndex[4] = n + 2;
        pIndex[5] = n + 3;
    }
}

void MakeRepeatedSurfaceMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, GLuint width, GLuint height)
{
    GLfloat vw = width + 1.0f;
    GLfloat vh = height + 1.0f;

    GLfloat half_w = width * 0.5f;
    GLfloat half_h = height * 0.5f;

    vertices.reserve((vw + 1) * (vh + 1));
    indices.reserve(width * height * 6);

    for (GLfloat i = 0; i < vh; i += 1.0f)
    {
        for (GLfloat j = 0; j < vw; j += 1.0f)
        {
            auto& vertex = vertices.emplace_back();

            vertex.pos.x = j - half_w;
            vertex.pos.z = i - half_h;
            vertex.uv.x = j;
            vertex.uv.y = i;
        }
    }

    for (GLuint i = 0; i < height; ++i)
    {
        for (GLuint j = 0; j < width; ++j)
        {
            GLuint pos = i * vw + j;

            indices.push_back(pos);
            indices.push_back(pos + 1);
            indices.push_back(pos + vw);

            indices.push_back(pos + 1);
            indices.push_back(pos + vw);
            indices.push_back(pos + vw + 1);
        }
    }
}