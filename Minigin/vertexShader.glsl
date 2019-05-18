#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in int texID;
layout(location = 2) in int id;

out vec2 texCoord0;

void main()
{
	gl_Position.x = ((pos.x)  / 640.0f) * 2.0f -1.0f;
	gl_Position.y = (pos.y  / 480.0f) * 2.0f -1.0f;
	gl_Position.z = pos.z;
	gl_Position.w = 1.0f;

	float tileSize = 0.5f;
	float row = float(id/2);
	float column = float(id%2);

    vec2 uv = vec2(0,0);
	switch(texID)
	{
		case 0:
			uv.x = column*tileSize;
			uv.y = row*tileSize;
		break;
		
		case 1:
			uv.x = (column+1)*tileSize;
			uv.y = row*tileSize;
		break;
		
		case 2:
			uv.x = column*tileSize;
			uv.y = (row+1)*tileSize;
		break;
		
		case 3:
			uv.x = (column+1)*tileSize;
			uv.y = (row+1)*tileSize;
		break;
	}
	uv.y = 1.0f-uv.y;

	texCoord0 = uv;
}