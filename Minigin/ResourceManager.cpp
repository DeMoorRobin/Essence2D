#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"


void dae::ResourceManager::Init(std::string&& dataPath)
{
	m_DataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}


//this method of handling textures is based on how it was done during prog2
dae::Texture2D dae::ResourceManager::LoadTexture(const std::string& file)
{

	if (m_Textures.find(file) != m_Textures.cend())
		return m_Textures[file];

	std::string fullPath{ m_DataPath + file };
	SDL_Surface* pSurface = IMG_Load(fullPath.c_str());
	if (!pSurface)
	{
		std::cerr << "IMG load failed " << file << std::endl;
	}

	

	GLenum pixelFormat{ GL_RGB };
	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR;
		}
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA;
		}
		break;
	default:
		std::cerr << "unknow pixel formatn : " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";
		return Texture2D{0,0,0};
	}
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	return Texture2D{float(pSurface->w),float(pSurface->h),id};

}

dae::Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	return new Font(m_DataPath + file, size);
}
