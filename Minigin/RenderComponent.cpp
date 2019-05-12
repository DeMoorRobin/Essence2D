#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"

//#include <glm/gtc/matrix_transform.hpp>

dae::Renderer* dae::RenderComponent::s_pRenderer{};

dae::RenderComponent::RenderComponent()
	:m_Texture{0,0,0}
{
}

dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Draw()
{
	glPushMatrix();
	glTranslatef(m_TransformComponent.GetPosition().x-m_DestRect.w/2.0f, m_TransformComponent.GetPosition().y-m_DestRect.h/2.0f, 0);

	m_DestRect.y = 20;
	s_pRenderer->RenderTexture(m_Texture, m_DestRect, m_SourceRect);
	glPopMatrix();
}

//const SDL_Rect& dae::RenderComponent::GetImageDimensions() 
//{
//	//this function needs to be completed bcause it will cause crashes
//	return SDL_Rect{};
//	//return m_pTexture->GetImageDimensions();
//};

void dae::RenderComponent::SetDestRectDefaultSize(int xSize, int ySize)
{
	m_DestRect.w = xSize;
	m_DestRect.h = ySize;
}

void dae::RenderComponent::SetSourceRect(const SDL_Rect& rect)
{
	m_SourceRect = rect;
}

void dae::RenderComponent::SetTransform(TransformComponent* pTransform)
{
	m_TransformComponent = *pTransform;
}

void dae::RenderComponent::SetStringTexture(const std::string & , TTF_Font * )
{
}

void dae::RenderComponent::SetTexture(dae::Texture2D texture)
{
	m_Texture = texture;
	m_DestRect.w = int(texture.GetWidth());
	m_DestRect.h = int(texture.GetHeight());
}