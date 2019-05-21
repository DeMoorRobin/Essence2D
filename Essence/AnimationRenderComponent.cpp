#include "MiniginPCH.h"
#include "AnimationRenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Time.h"

dae::AnimationRenderComponent::AnimationRenderComponent(const std::string& textureFile, float defaultXSize, float defaultYSize)
	:BaseComponent{true}
	,m_VertexID{}
	,m_DefaultXSize{defaultXSize}
	,m_DefaultYSize{defaultYSize}
	,m_TextureFile{textureFile}
	,m_CurrentAnimation{}
	,m_CurrentFrame{}
	,m_pFrames{}
	,m_IdToAnimMap{}
{

}

dae::AnimationRenderComponent::~AnimationRenderComponent()
{
	for (auto* f : m_pFrames)
	{
		delete f;
	}
}

void dae::AnimationRenderComponent::AddAnimation(std::vector<Frame>* pAnimation, int id)
{
	m_pFrames.push_back(pAnimation);
	m_IdToAnimMap[id] = m_pFrames.size() - 1;
}

void dae::AnimationRenderComponent::SetCurrentAnimation(int id, float timePerFrame, int startFrame, bool restarOnSame)
{
	if (m_IdToAnimMap.find(id) != m_IdToAnimMap.end())
	{
		if (m_IdToAnimMap[id] != m_CurrentAnimation || restarOnSame)
		{
			m_CurrentAnimation = m_IdToAnimMap[id];
			m_FrameDuration = timePerFrame;
			m_ElapsedTime = 0;
			m_CurrentFrame = startFrame;
		}
	}
	else std::cout << "animation id out of range \n";
		
}


void dae::AnimationRenderComponent::Initialize()
{
	m_pGameObject->GetRenderComponent()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture(m_TextureFile));
	m_pGameObject->GetRenderComponent()->SetRenderType(dae::RenderType::SPRITE);
	m_pGameObject->GetRenderComponent()->SetProgram(dae::ResourceManager::GetInstance().LoadShaders("../Essence/spriteVS.glsl", "../Essence/spritePS.glsl", "../Essence/spriteGS.glsl"));

	std::vector<GLfloat> center{};
	center.push_back(m_pGameObject->GetTransform()->GetPosition().x);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().y);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().z);
	center.push_back(m_DefaultXSize * m_pGameObject->GetTransform()->GetScale().x);
	center.push_back(m_DefaultYSize * m_pGameObject->GetTransform()->GetScale().y);
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(0));
	glGenBuffers(1, &m_VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * center.size(), center.data(), GL_DYNAMIC_DRAW);
	m_pGameObject->GetRenderComponent()->SetBuffers(m_VertexID, 0);
}

void dae::AnimationRenderComponent::Update()
{
	m_ElapsedTime += dae::Time::GetInstance().GetDeltaTime();
	if (m_ElapsedTime >= m_FrameDuration)
	{
		m_ElapsedTime = 0;
		++m_CurrentFrame;
		if (m_CurrentFrame >= m_pFrames[m_CurrentAnimation]->size())
			m_CurrentFrame = 0;
	}

	
	std::vector<GLfloat> center{};
	center.push_back(m_pGameObject->GetTransform()->GetPosition().x);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().y);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().z);
	center.push_back(m_DefaultXSize * m_pGameObject->GetTransform()->GetScale().x);
	center.push_back(m_DefaultYSize * m_pGameObject->GetTransform()->GetScale().y);
	center.push_back(GLfloat(m_pFrames[m_CurrentAnimation]->at(m_CurrentFrame).left));
	center.push_back(GLfloat(m_pFrames[m_CurrentAnimation]->at(m_CurrentFrame).bottom));
	center.push_back(GLfloat(m_pFrames[m_CurrentAnimation]->at(m_CurrentFrame).width));
	center.push_back(GLfloat(m_pFrames[m_CurrentAnimation]->at(m_CurrentFrame).height));

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*center.size(), center.data());
}
