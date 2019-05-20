#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 texCoord;

in VS_OUT
{
	vec2 size;
	vec4 sourceRect;
}gs_in[];

vec4 ToNDC(vec4 pos)
{
	pos.x = ((pos.x)  / 640.0f) * 2.0f -1.0f;
	pos.y = (pos.y  / 480.0f) * 2.0f -1.0f;
	clamp(pos.z, 0.0, 1.0);
	return pos;
}

void main()
{
	gl_Position = ToNDC(gl_in[0].gl_Position + vec4(-gs_in[0].size.x/2.0f,-gs_in[0].size.y/2.0f,gl_in[0].gl_Position.z,0));
	texCoord = vec2(gs_in[0].sourceRect.x,gs_in[0].sourceRect.y);
	EmitVertex();

	gl_Position = ToNDC(gl_in[0].gl_Position + vec4(gs_in[0].size.x/2.0f,-gs_in[0].size.y/2.0f,gl_in[0].gl_Position.z,0));
	texCoord = vec2(gs_in[0].sourceRect.x + gs_in[0].sourceRect.z,gs_in[0].sourceRect.y);
	EmitVertex();

	gl_Position = ToNDC(gl_in[0].gl_Position + vec4(-gs_in[0].size.x/2.0f,gs_in[0].size.y/2.0f,gl_in[0].gl_Position.z,0));
	texCoord = vec2(gs_in[0].sourceRect.x,gs_in[0].sourceRect.y + gs_in[0].sourceRect.w);
	EmitVertex();

	gl_Position = ToNDC(gl_in[0].gl_Position + vec4(gs_in[0].size.x/2.0f,gs_in[0].size.y/2.0f,gl_in[0].gl_Position.z,0));
	texCoord = vec2(gs_in[0].sourceRect.x + gs_in[0].sourceRect.z,gs_in[0].sourceRect.y+ gs_in[0].sourceRect.w);
	EmitVertex();

	EndPrimitive();
}