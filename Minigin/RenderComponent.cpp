#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"

#include <GL/GL.h>
#include <GL/GLU.h>

dae::Renderer* dae::RenderComponent::s_pRenderer{};

dae::RenderComponent::RenderComponent()
{
}


dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Draw()
{
	glPushMatrix();
	glTranslatef(m_TransformComponent.GetPosition().x, m_TransformComponent.GetPosition().y, 0);
	SDL_RenderCopy(s_pRenderer->GetSDLRenderer(), m_pTexture->GetSDLTexture(), &m_SourceRect, &m_DestRect);
	glPopMatrix();
}

const SDL_Rect& dae::RenderComponent::GetImageDimensions() 
{
	return m_pTexture->GetImageDimensions();
};

void dae::RenderComponent::SetDestRectDefaultSize(float xSize, float ySize)
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