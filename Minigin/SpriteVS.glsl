#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 size;
layout(location = 2) in vec4 sourceRect;

out VS_OUT
{
	vec2 size;
	vec4 sourceRect;
}vs_out;

void main()
{
	gl_Position = vec4(pos,1);
	vs_out.size = size;
	vs_out.sourceRect = sourceRect;
}