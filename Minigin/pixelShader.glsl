#version 330 core

uniform sampler2D baseImage;

in vec2 texCoord;
out vec3 color;

void main()
{
	vec2 uv = texCoord;
	uv.y = 1-texCoord.y;
	color = texture(baseImage, texCoord).xyz;
}

