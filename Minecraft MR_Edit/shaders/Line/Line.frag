#version 330 core

out vec4 FragColor;

uniform vec4 lineColor;
in vec4 color;

void main()
{
	FragColor = color;
} 