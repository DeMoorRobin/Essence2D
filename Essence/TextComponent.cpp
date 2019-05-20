#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
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
{
	m_pFont = new dae::Font(fontPath, fontSize);
	Initialize();
}


dae::TextComponent::~TextComponent()
{
	delete m_pFont;
	m_Texture.ReleaseID();
}


void dae::TextComponent::Initialize()
{
	//const SDL_Color color = { 255,255,255 };
	//const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	//if (surf == nullptr)
	//{
	//	throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	//}
	//m_pTexture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	//if (m_pTexture == nullptr)
	//{
	//	throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	//}
	//SDL_FreeSurface(surf);
}
void dae::TextComponent::Update()
{
	m_Text = std::to_string(Time::GetInstance().GetFPS());
	m_Texture.ReleaseID();
	m_Texture = ResourceManager::GetInstance().LoadStringTexture(m_pFont->GetFont(), m_Text);
	m_pGameObject->GetRenderComponent()->SetTexture(m_Texture);
	
}
//void dae::TextComponent::Draw()
//{
//	if (m_pTexture != nullptr)
//	{
//		dae::Renderer::GetInstance().RenderTexture(m_pTexture, 0.0f,0.0f);
//	}
//}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
}