#include "MiniginPCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "GameObject.h"

dae::ImageComponent::ImageComponent(const std::string& textureFile, float defaultXSize, float defaultYSize, glm::vec4 UVBottomLeftSourceRect)
	:BaseComponent{true}
	, m_VertexID{}
	, m_DefaultXSize{defaultXSize}
	, m_DefaultYSize{defaultYSize}
	, m_TextureFile{textureFile}
	, m_UVSourceRect{UVBottomLeftSourceRect}
{
}


void dae::ImageComponent::Initialize()
{
	m_pGameObject->GetRenderComponent()->SetTexture( dae::ResourceManager::GetInstance().LoadTexture(m_TextureFile));
	m_pGameObject->GetRenderComponent()->SetRenderType(dae::RenderType::SPRITE);
	m_pGameObject->GetRenderComponent()->SetProgram(dae::ResourceManager::GetInstance().LoadShaders("../Essence/spriteVS.glsl", "../Essence/spritePS.glsl", "../Essence/spriteGS.glsl"));

	std::vector<GLfloat> center{};
	center.push_back(m_pGameObject->GetTransform()->GetPosition().x);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().y);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().z);
	center.push_back(m_DefaultXSize * m_pGameObject->GetTransform()->GetScale().x);
	center.push_back(m_DefaultYSize * m_pGameObject->GetTransform()->GetScale().y);
	center.push_back(GLfloat(m_UVSourceRect.x));
	center.push_back(GLfloat(m_UVSourceRect.y));
	center.push_back(GLfloat(m_UVSourceRect.z));
	center.push_back(GLfloat(m_UVSourceRect.w));
	auto er = glGetError();
	if (er != GL_NO_ERROR)
	{
		std::cout << er << std::endl;
	}

	glGenBuffers(1, &m_VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * center.size(), center.data(), GL_STATIC_DRAW);
	m_pGameObject->GetRenderComponent()->SetBuffers(m_VertexID, 0);

	er = glGetError();
	if (er != GL_NO_ERROR)
	{
		std::cout << er << std::endl;
	}

}

void dae::ImageComponent::Update()
{
	auto er = glGetError();
	if (er != GL_NO_ERROR)
	{
		std::cout << er << std::endl;
	}

	std::vector<GLfloat> center{};
	center.push_back(m_pGameObject->GetTransform()->GetPosition().x);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().y);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().z);
	center.push_back(m_DefaultXSize * m_pGameObject->GetTransform()->GetScale().x);
	center.push_back(m_DefaultYSize * m_pGameObject->GetTransform()->GetScale().y);
	center.push_back(GLfloat(m_UVSourceRect.x));
	center.push_back(GLfloat(m_UVSourceRect.y));
	center.push_back(GLfloat(m_UVSourceRect.z));
	center.push_back(GLfloat(m_UVSourceRect.w));

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*center.size(), center.data());

	er = glGetError();
	if (er != GL_NO_ERROR)
	{
		std::cout << er << std::endl;
	}
	//glReleaseBuffer
	//glGenBuffers(1, &m_VertexID);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * center.size(), center.data(), GL_DYNAMIC_DRAW);
	//m_pGameObject->GetRenderComponent()->SetBuffers(m_VertexID,0);
}