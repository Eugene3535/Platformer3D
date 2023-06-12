#ifndef DEFINES_HPP
#define DEFINES_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#define DEGTORAD 0.017453f
#define RADTODEG 57.29577f

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

#endif