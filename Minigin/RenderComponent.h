#pragma once
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
#include <SDL_image.h>
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
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


		const SDL_Rect& GetImageDimensions();

		void Draw();
		void SetDestRectDefaultSize(float xSize, float ySize);
		void SetSourceRect(const SDL_Rect& rect);
		void SetTransform(TransformComponent* pTransform);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		SDL_Rect m_SourceRect;
		SDL_Rect m_DestRect;
		TransformComponent m_TransformComponent;
		static Renderer* s_pRenderer;
		

	};


}
