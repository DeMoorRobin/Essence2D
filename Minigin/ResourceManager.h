#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "Texture2D.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string m_DataPath;
		
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		Texture2D LoadTexture(const std::string& file);
		Texture2D LoadStringTexture(TTF_Font *pFont, const std::string& text);
		Font* LoadFont(const std::string& file, unsigned int size);
		std::unordered_map<std::string, Texture2D> m_Textures;
	};

}
