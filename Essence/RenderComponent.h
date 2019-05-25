#pragma once
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
#include <SDL_image.h>
#include "TransformComponent.h"
#include "Texture2D.h"

namespace dae
{
	enum class RenderType
	{
		SPRITE,GRID
	};
	class Renderer;
	class TransformComponent;
	class RenderComponent
	{
	public:
		RenderComponent();

		//const SDL_Rect& GetImageDimensions();

		friend bool operator== (const RenderComponent &lhs, const RenderComponent &rhs)
		{
			return lhs.m_pTransformComponent == rhs.m_pTransformComponent;
		}

		void Draw();
		void SetTexture(Texture2D texture);
		void SetTransform(TransformComponent* pTransform);
		void SetStringTexture(const std::string& text, TTF_Font* pFont);
		float GetDepth() { return m_pTransformComponent->GetPosition().z; };

		void SetProgram(GLuint id) { m_ProgramID = id; };
		void SetBuffers(GLuint vertexID, GLuint indexID) { m_VertexBufferID = vertexID; m_IndexBufferID = indexID; };
		void SetIndexCount(GLuint count) { m_IndexCount = count; };
		void SetRenderType(RenderType type) { m_RenderType = type; };
	private:
		TransformComponent* m_pTransformComponent;
		Texture2D m_Texture;
		static Renderer* s_pRenderer;

		GLuint m_ProgramID,m_VertexBufferID,m_IndexBufferID;
		GLuint m_IndexCount;
		RenderType m_RenderType;

		void DrawGrid();
		void DrawSprite();

	};


}
