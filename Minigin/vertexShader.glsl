#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

out vec2 texCoord0;

void main()
{
	gl_Position.x = ((pos.x)  / 640.0f) * 2.0f -1.0f;
	gl_Position.y = (pos.y  / 480.0f) * 2.0f -1.0f;
	gl_Position.z = pos.z;
	gl_Position.w = 1.0f;
	texCoord0 = texCoord;

}