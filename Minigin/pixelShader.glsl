#version 330 core

uniform sampler2D baseImage;

in vec2 texCoord0;

out vec3 color;

void main()
{
	color = texture(baseImage, texCoord0).xyz;
}

