#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& dest, const SDL_Rect& src = SDL_Rect{}) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

