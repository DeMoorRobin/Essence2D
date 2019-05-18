#version 330 core

uniform sampler2D baseImage;
in vec2 texCoord0;

out vec3 color;



void main()
{
	vec2 uv = texCoord0;
	uv.y = 1.0f-texCoord0.y;
	color = texture(baseImage, uv).xyz;
}

