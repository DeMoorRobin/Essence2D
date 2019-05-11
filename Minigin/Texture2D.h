#pragma once
struct SDL_Texture;
#include "SDL_rect.h"

namespace dae
{
	class Texture2D
	{
	public:;
		explicit Texture2D(float width, float height, GLuint id);

		//Texture2D is supposed to have copies. Unlike the name suggests it does not contain a texture. just the id of the bound gl tex

		float GetWidth() const { return m_Width; };
		float GetHeight() const { return m_Height; };
	private:
		const float m_Width;
		const float m_Height;
		const GLuint m_ID;
	};
}
