#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;
layout (location = 3) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
 
out vec2 texcoord;
out vec4 color;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);

    texcoord = aTexcoord;
    color = aColor;
}