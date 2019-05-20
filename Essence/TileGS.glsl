#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 texCoord;

in VS_OUT
{
	int id;
} gs_in[];


vec4 ToNDC(vec4 pos)
{
	pos.x = ((pos.x)  / 640.0f) * 2.0f -1.0f;
	pos.y = (pos.y  / 480.0f) * 2.0f -1.0f;
	clamp(pos.z, 0.0, 1.0);
	return pos;
}

void main() 
{    
	float halfSize = 2.5f;
	float row = float(gs_in[0].id / 2);
	float column = float(gs_in[0].id % 2);
	//float row = 0;
	//float column = 0;
	float tileTexSize = 0.5f;

	if(gs_in[0].id != 999)
	{
		//gl_Position = gl_in[0].gl_Position + vec4(-halfSize,-halfSize,0,0);
		gl_Position = ToNDC(gl_in[0].gl_Position + vec4(-halfSize,-halfSize,0,0));
		texCoord = vec2(tileTexSize*column,tileTexSize*row);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(halfSize,-halfSize,0,0);
		gl_Position = ToNDC(gl_Position);
		texCoord = vec2(tileTexSize*(column+1),tileTexSize*row);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(-halfSize,halfSize,0,0);
		gl_Position = ToNDC(gl_Position);
		texCoord = vec2(tileTexSize*column,tileTexSize*(1+row));
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(halfSize,halfSize,0,0);
		gl_Position = ToNDC(gl_Position);
		texCoord = vec2(tileTexSize*(column+1),tileTexSize*(1+row));
		EmitVertex();

		EndPrimitive();
	}
	else EndPrimitive();
   
}  