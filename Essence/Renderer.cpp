#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include <algorithm>

void dae::Renderer::Init(SDL_Window *)
{
	//mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if (mRenderer == nullptr) 
	//{
	//	throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	//}
}

void dae::Renderer::Render()
{
	
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D & texture, const SDL_Rect & dest, const SDL_Rect & src) const
{
	float leftUV,rightUV,topUV,botUV; //texture coords
	if (src.w == 0.0f && src.h == 0.0f)
	{
		leftUV = 0;
		rightUV = 1.0f;
		topUV = 0.0f;
		botUV = 1.0f;
	}
	else
	{
		leftUV = src.x / texture.GetWidth();
		rightUV = (src.x + src.w) / texture.GetWidth();
		topUV = (src.y - src.h) / texture.GetHeight();
		botUV = src.y / texture.GetHeight();
	}

	float left, right, top, bot;
	left = float(dest.x);
	bot = float(dest.y);
	if (src.w == 0.0f && src.h == 0.0f)
	{
		right = left + texture.GetWidth();
		top = bot + texture.GetHeight();
	}
	else
	{
		right = left + dest.w;
		top = bot + dest.h;
	}

	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(leftUV, botUV);
			glVertex2f(left, bot);

			glTexCoord2f(leftUV, topUV);
			glVertex2f(left, top);

			glTexCoord2f(rightUV, topUV);
			glVertex2f(right, top);

			glTexCoord2f(rightUV, botUV);
			glVertex2f(right, bot);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	//glBegin(GL_QUADS);
	//{
	//	//glTexCoord2f(leftUV, botUV);
	//	glVertex2f(left, bot);
	//
	//	//glTexCoord2f(leftUV, topUV);
	//	glVertex2f(left, top);
	//
	//	//glTexCoord2f(rightUV, topUV);
	//	glVertex2f(right, top);
	//
	//	//glTexCoord2f(rightUV, botUV);
	//	glVertex2f(right, bot);
	//}
	//glEnd();
}

void dae::Renderer::Draw()
{
	Sort();
	for (RenderComponent& r : m_RenderComponents)
	{
		r.Draw();
	}

}

void dae::Renderer::Sort()
{
}

dae::RenderComponent* dae::Renderer::RequestRenderComponent()
{
	m_RenderComponents.push_back(RenderComponent{});
	return &m_RenderComponents.back();
	//return nullptr;
}