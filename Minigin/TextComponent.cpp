#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Time.h"
#include <string>

dae::TextComponent::TextComponent(const std::string& text, const std::string& fontPath, unsigned int fontSize)
	:m_pFont{ nullptr }
	,m_Text{ text }
{
	m_pFont = new dae::Font(fontPath, fontSize);
	Initialize();
}


dae::TextComponent::~TextComponent()
{
	delete m_pFont;
	SDL_DestroyTexture(m_pTexture);
}


void dae::TextComponent::Initialize()
{
	const SDL_Color color = { 255,255,255 };
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	m_pTexture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (m_pTexture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
}
void dae::TextComponent::Update()
{
	m_Text = std::to_string(Time::GetInstance().GetFPS());
	SDL_DestroyTexture(m_pTexture);
	Initialize();
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