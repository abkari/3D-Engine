#version 330 core

out vec4 FragColor;

in vec2 texcoord;
in vec4 color;

uniform sampler2D albedo;

void main()
{
    FragColor = texture(albedo, texcoord);
} 