#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "Time.h"

//#include <glm/gtc/matrix_transform.hpp>

dae::Renderer* dae::RenderComponent::s_pRenderer{ &dae::Renderer::GetInstance() };

dae::RenderComponent::RenderComponent()
	:m_Texture{0,0,0}
	,m_VertexBufferID{}
	,m_IndexBufferID{}
	,m_ProgramID{}
	,m_IndexCount{}
	,m_RenderType{}
{
}


void dae::RenderComponent::Draw()
{
	switch(m_RenderType)
	{
	case RenderType::SPRITE :
		DrawSprite();		
		break;
	case RenderType::GRID :
		//if(Time::GetInstance().GetFrameCounter() < 80)
		DrawGrid();
		break;		
	}
	//glInvalidateBufferData(m_VertexBufferID);
	//glInvalidateBufferData(m_IndexBufferID);
	
}

//const SDL_Rect& dae::RenderComponent::GetImageDimensions() 
//{
//	//this function needs to be completed bcause it will cause crashes
//	return SDL_Rect{};
//	//return m_pTexture->GetImageDimensions();
//};



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
}


void dae::RenderComponent::DrawSprite()
{
	glUseProgram(m_ProgramID);
	auto e = glGetError();
	if (e != GL_NO_ERROR) std::cout << e << std::endl;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture.GetID());

	e = glGetError();

	auto loc = glGetUniformLocation(m_ProgramID, "baseImage");
	glUniform1i(loc, 0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	e = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	e = glGetError();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)12);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)20);
	e = glGetError();
	glActiveTexture(GL_TEXTURE0);
	glDrawArrays(GL_POINTS, 0, 1);
	e = glGetError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void dae::RenderComponent::DrawGrid()
{
	auto e = glGetError();
	if (e != GL_NO_ERROR) std::cout << e << std::endl;

	glUseProgram(m_ProgramID);
	e = glGetError();

	glActiveTexture(GL_TEXTURE0);
	e = glGetError();
	glBindTexture(GL_TEXTURE_2D, m_Texture.GetID());
	e = glGetError();
	auto loc = glGetUniformLocation(m_ProgramID, "baseImage");
	glUniform1i(loc, 0);
	e = glGetError();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	e = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	e = glGetError();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)0);
	glVertexAttribIPointer(1, 1, GL_INT, sizeof(float) * 4, (GLvoid*)12);
	//glVertexAttribIPointer(2, 1, GL_INT, sizeof(float) * 5, (GLvoid*)16);
	e = glGetError();


	glActiveTexture(GL_TEXTURE0);
	glDrawArrays(GL_POINTS, 0, m_IndexCount);
	//glDrawElements(GL_POINTS, m_IndexCount, GL_UNSIGNED_INT, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
}