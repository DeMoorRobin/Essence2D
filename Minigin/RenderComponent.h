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

		//const SDL_Rect& GetImageDimensions();

		void Draw();
		void SetTexture(Texture2D texture);
		void SetDestRectDefaultSize(int xSize, int ySize);
		void SetSourceRect(const SDL_Rect& rect);
		void SetTransform(TransformComponent* pTransform);
		void SetStringTexture(const std::string& text, TTF_Font* pFont);
		void SetSpriteBased(bool enable) { m_IsSpriteBased = enable; };
		int GetDepth() { return int(m_pTransformComponent->GetPosition().z); };

		void SetProgram(GLuint id) { m_ProgramID = id; };
		void SetBuffers(GLuint vertexID, GLuint indexID) { m_VertexBufferID = vertexID; m_IndexBufferID = indexID; };
		void SetIndexCount(GLuint count) { m_IndexCount = count; };

	private:
		TransformComponent* m_pTransformComponent;
		SDL_Rect m_DestRect;
		Texture2D m_Texture;
		SDL_Rect m_SourceRect;
		static Renderer* s_pRenderer;

		bool m_IsSpriteBased;
		GLuint m_ProgramID,m_VertexBufferID,m_IndexBufferID;
		GLuint m_IndexCount;

	};


}
