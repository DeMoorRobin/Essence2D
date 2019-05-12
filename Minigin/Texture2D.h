#pragma once
struct SDL_Texture;
#include "SDL_rect.h"

namespace dae
{
	class Texture2D
	{
	public:
		Texture2D(float width, float height, GLuint id);
		Texture2D();
		~Texture2D();
		
		//Texture2D is supposed to have copies. Unlike the name suggests it does not contain a texture. just the id of the bound gl tex

		void ReleaseID() { glDeleteTextures(1, &m_ID); };
		float GetWidth() const { return m_Width; };
		float GetHeight() const { return m_Height; };
		GLuint GetID() const { return m_ID; };
	private:
		float m_Width;
		float m_Height;
		GLuint m_ID;
	};
}
