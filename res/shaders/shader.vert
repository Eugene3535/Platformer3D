#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);
uniform vec4 inColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec2 tex_coord;
out vec4 color;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0f);
    tex_coord = inTexCoord;
    color = inColor;
}