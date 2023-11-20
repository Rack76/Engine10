#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 cameraTransform = mat4(1.0);
uniform mat4 perspective;
uniform mat4 objectTransform = mat4(1.0);

void main()
{
    gl_Position = vec4(position, 1.0) * objectTransform * cameraTransform * perspective;
}