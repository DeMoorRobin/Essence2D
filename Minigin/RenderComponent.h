#pragma once
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
#include <SDL_image.h>
#include "TransformComponent.h"
#include "Texture2D.h"

namespace dae
{
	class Renderer;
	class TransformComponent;
	class RenderComponent
	{
	public:
		RenderComponent();
		//~RenderComponent();

		//RenderComponent(const RenderComponent&) = delete;
		//RenderComponent(RenderComponent &&) = delete;
		//RenderComponent &operator=(const RenderComponent &) = delete;
		//RenderComponent &operator=(const RenderComponent &&) = delete;


		//const SDL_Rect& GetImageDimensions();

		void Draw();
		void SetTexture(Texture2D texture);
		void SetDestRectDefaultSize(int xSize, int ySize);
		void SetSourceRect(const SDL_Rect& rect);
		void SetTransform(TransformComponent* pTransform);
		void SetStringTexture(const std::string& text, TTF_Font* pFont);
		int GetDepth() { return int(m_TransformComponent.GetPosition().z); };

	private:
		TransformComponent m_TransformComponent;
		SDL_Rect m_DestRect;
		Texture2D m_Texture;
		SDL_Rect m_SourceRect;
		static Renderer* s_pRenderer;
		

	};


}
