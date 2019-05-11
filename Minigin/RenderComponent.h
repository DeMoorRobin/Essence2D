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
		~RenderComponent();

		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent &&) = delete;
		RenderComponent &operator=(const RenderComponent &) = delete;
		RenderComponent &operator=(const RenderComponent &&) = delete;


		//const SDL_Rect& GetImageDimensions();

		void Draw();
		void SetTexture(Texture2D texture);
		void SetDestRectDefaultSize(int xSize, int ySize);
		void SetSourceRect(const SDL_Rect& rect);
		void SetTransform(TransformComponent* pTransform);
	private:
		Texture2D m_Texture;
		SDL_Rect m_SourceRect;
		SDL_Rect m_DestRect;
		TransformComponent m_TransformComponent;
		static Renderer* s_pRenderer;
		

	};


}
