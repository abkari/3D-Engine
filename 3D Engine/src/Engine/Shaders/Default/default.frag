#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec2 texcoord;

uniform sampler2D albedo;

void main()
{
	fragColor = texture(albedo, texcoord);
}