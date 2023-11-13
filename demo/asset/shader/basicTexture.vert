#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vsTexCoord;

out vec2 fsTexCoord;

void main()
{
    gl_Position = vec4(position, 1.0);
    fsTexCoord = vsTexCoord;
}