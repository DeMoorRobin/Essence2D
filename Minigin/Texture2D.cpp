#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::Texture2D(float width, float height, GLuint id)
	:m_Width{width}
	,m_Height{height}
	,m_ID{id}
{
}

dae::Texture2D::Texture2D()
	:m_Width{}
	, m_Height{}
	, m_ID{}
{

}

dae::Texture2D::~Texture2D()
{
}
