#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"

//#include <glm/gtc/matrix_transform.hpp>

dae::Renderer* dae::RenderComponent::s_pRenderer{};

dae::RenderComponent::RenderComponent()
	:m_Texture{0,0,0}
	,m_SourceRect{}
	,m_DestRect{}
	,m_IsSpriteBased{true}
{
}


void dae::RenderComponent::Draw()
{
	if (m_IsSpriteBased)
	{
		glPushMatrix();
		glTranslatef(m_pTransformComponent->GetPosition().x - m_DestRect.w / 2.0f*m_pTransformComponent->GetScale().x, m_pTransformComponent->GetPosition().y- m_DestRect.h/ 2.0f*m_pTransformComponent->GetScale().y, 0);
		glScalef(m_pTransformComponent->GetScale().x, m_pTransformComponent->GetScale().y, 1.0f);
		glTranslatef(GLfloat(-m_DestRect.x), GLfloat(-m_DestRect.y), 0);
		s_pRenderer->RenderTexture(m_Texture, m_DestRect, m_SourceRect);
		glPopMatrix();
	}
	else
	{
		glUseProgram(m_ProgramID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture.GetID());
		auto loc = glGetUniformLocation(m_ProgramID, "baseImage");
		glUniform1f(loc, 0);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)12);
		glActiveTexture(GL_TEXTURE0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, (GLvoid*)0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	}
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
	m_pTransformComponent = pTransform;
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