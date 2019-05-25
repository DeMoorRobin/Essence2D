#version 330 core
uniform sampler2D baseImage;
in vec2 texCoord;

out vec3 color;

void main()
{
	vec2 uv = texCoord;
	uv.y = 1-texCoord.y;
	color = texture(baseImage, uv).xyz;
	if(color.x == 0 && color.y == 0 && color.z == 0)discard;
}