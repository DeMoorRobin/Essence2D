#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in int id;


out VS_OUT
{
	int id;
} vs_out;


void main()
{
	gl_Position = vec4(pos,1.0);
	vs_out.id = id;
	//gl_Position.x = ((pos.x)  / 640.0f) * 2.0f -1.0f;
	//gl_Position.y = (pos.y  / 480.0f) * 2.0f -1.0f;
	//gl_Position.z = pos.z;
	//gl_Position.w = 1.0f;
	//switch(texID)
	//{
	//	case -1:
	//		shouldClip = 1;
	//		break;
	//	case 0:
	//		uv.x = column*tileSize;
	//		uv.y = row*tileSize;
	//	break;
	//	
	//	case 1:
	//		uv.x = (column+1)*tileSize;
	//		uv.y = row*tileSize;
	//	break;
	//	
	//	case 2:
	//		uv.x = column*tileSize;
	//		uv.y = (row+1)*tileSize;
	//	break;
	//	
	//	case 3:
	//		uv.x = (column+1)*tileSize;
	//		uv.y = (row+1)*tileSize;
	//	break;
	//}
	
}