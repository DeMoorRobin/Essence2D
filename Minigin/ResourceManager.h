#pragma once
#include "Singleton.h"
#include <unordered_map>

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string m_DataPath;
		Texture2D LoadTexture(const std::string& file);
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		Font* LoadFont(const std::string& file, unsigned int size);
		
		std::unordered_map<std::string, Texture2D> m_Textures;
	};

}
