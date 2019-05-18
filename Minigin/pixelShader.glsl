#version 330 core

uniform sampler2D baseImage;

in vec2 texCoord0;
flat in int shouldClip;
out vec3 color;

void main()
{
	if(shouldClip == 1) discard;
	color = texture(baseImage, texCoord0).xyz;
}

