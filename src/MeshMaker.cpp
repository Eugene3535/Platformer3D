#include "MeshMaker.hpp"

void MakeCubeMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const glm::vec3& minPt, const glm::vec3& maxPt, const glm::vec2* uv)
{
    const static glm::vec2 cubeUV[] = // one texture on all faces by default
    {
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 1.0f }
    };

    if( ! uv)
    {
        vertices = 
        {
    //      Front
            {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), cubeUV[0]},
            {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), cubeUV[1]},
            {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), cubeUV[2]},
            {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), cubeUV[3]},
    //      Back
            {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), cubeUV[0]},
            {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), cubeUV[1]},
            {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), cubeUV[2]},
            {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), cubeUV[3]},
    //      Bottom
            {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), cubeUV[0]},
            {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), cubeUV[1]},
            {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), cubeUV[2]},
            {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), cubeUV[3]},
    //      Top
            {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), cubeUV[0]},
            {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), cubeUV[1]},
            {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), cubeUV[2]},
            {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), cubeUV[3]},
    //      Left
            {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), cubeUV[0]},
            {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), cubeUV[1]},
            {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), cubeUV[2]},
            {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), cubeUV[3]},
    //      Right
            {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), cubeUV[0]},
            {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), cubeUV[1]},
            {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), cubeUV[2]},
            {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), cubeUV[3]}
        };
    }
    else
    {
        vertices = 
        {
    //      Front
            {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), uv[0]},
            {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), uv[1]},
            {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), uv[2]},
            {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), uv[3]},
    //      Back
            {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), uv[4]},
            {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), uv[5]},
            {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), uv[6]},
            {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), uv[7]},
    //      Bottom
            {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), uv[8]},
            {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), uv[9]},
            {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), uv[10]},
            {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), uv[11]},
    //      Top
            {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), uv[12]},
            {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), uv[13]},
            {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), uv[14]},
            {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), uv[15]},
    //      Left
            {{ minPt.x, minPt.y, minPt.z }, glm::vec3(), uv[16]},
            {{ minPt.x, minPt.y, maxPt.z }, glm::vec3(), uv[17]},
            {{ minPt.x, maxPt.y, maxPt.z }, glm::vec3(), uv[18]},
            {{ minPt.x, maxPt.y, minPt.z }, glm::vec3(), uv[19]},
    //      Right
            {{ maxPt.x, minPt.y, maxPt.z }, glm::vec3(), uv[20]},
            {{ maxPt.x, minPt.y, minPt.z }, glm::vec3(), uv[21]},
            {{ maxPt.x, maxPt.y, minPt.z }, glm::vec3(), uv[22]},
            {{ maxPt.x, maxPt.y, maxPt.z }, glm::vec3(), uv[23]}
        };
    }

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

            vertex.position.x = j - half_w;
            vertex.position.z = i - half_h;
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