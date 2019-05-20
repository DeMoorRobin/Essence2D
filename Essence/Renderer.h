#pragma once
#include "Singleton.h"
#include "RenderComponent.h"
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;
		std::vector<RenderComponent> m_RenderComponents;
		void Sort();
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();
		void Draw();
		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& dest, const SDL_Rect& src = SDL_Rect{}) const;

		RenderComponent* RequestRenderComponent();

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

