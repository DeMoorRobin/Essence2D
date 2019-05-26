#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Time.h"
#include <string>
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(const std::string& text, const std::string& fontPath, unsigned int fontSize)
	:BaseComponent{true}
	,m_pFont{ nullptr }
	,m_Text{ text }
	,m_VertexID{}
	,m_Texture{}
	,m_HasTextChanged{}
{
	m_pFont = new dae::Font(fontPath, fontSize);
}


dae::TextComponent::~TextComponent()
{
	delete m_pFont;
	m_Texture.ReleaseID();
}


void dae::TextComponent::Initialize()
{
	m_pGameObject->GetRenderComponent()->SetRenderType(dae::RenderType::SPRITE);
	m_pGameObject->GetRenderComponent()->SetProgram(dae::ResourceManager::GetInstance().LoadShaders("../Essence/spriteVS.glsl", "../Essence/spritePS.glsl", "../Essence/spriteGS.glsl"));

	m_Texture.ReleaseID();
	m_Texture = ResourceManager::GetInstance().LoadStringTexture(m_pFont->GetFont(), m_Text);
	m_pGameObject->GetRenderComponent()->SetTexture(m_Texture);

	std::vector<GLfloat> center{};
	center.push_back(m_pGameObject->GetTransform()->GetPosition().x);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().y);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().z);
	center.push_back(m_Texture.GetWidth() * m_pGameObject->GetTransform()->GetScale().x);
	center.push_back(m_Texture.GetHeight() * m_pGameObject->GetTransform()->GetScale().y);
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(1.0f));
	center.push_back(GLfloat(1.0f));
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
void dae::TextComponent::Update()
{
	if (m_HasTextChanged)
	{
		m_Text = std::to_string(Time::GetInstance().GetFPS());
		m_Texture.ReleaseID();
		m_Texture = ResourceManager::GetInstance().LoadStringTexture(m_pFont->GetFont(), m_Text);
		m_pGameObject->GetRenderComponent()->SetTexture(m_Texture);
		m_HasTextChanged = false;
	}
	
	std::vector<GLfloat> center{};
	center.push_back(m_pGameObject->GetTransform()->GetPosition().x);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().y);
	center.push_back(m_pGameObject->GetTransform()->GetPosition().z);
	center.push_back(m_Texture.GetWidth() * m_pGameObject->GetTransform()->GetScale().x);
	center.push_back(m_Texture.GetHeight() * m_pGameObject->GetTransform()->GetScale().y);
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(0));
	center.push_back(GLfloat(1.0f));
	center.push_back(GLfloat(1.0f));

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*center.size(), center.data());
	
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_HasTextChanged = true;
}