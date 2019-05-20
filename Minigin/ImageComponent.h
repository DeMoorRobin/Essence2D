#pragma once
#include "BaseComponent.h"
namespace dae
{
	class ImageComponent final : public BaseComponent
	{
	public:
		ImageComponent(const std::string& textureFile, float defaultXSize, float defaultYSize, glm::vec4 UVBottomLeftSourceRect = glm::vec4{0.0f,0.0f,1.0f,1.0f});
		virtual ~ImageComponent() = default;
	protected:
		void Initialize() override;
		void Update() override;
	private:
		std::string m_TextureFile;
		glm::vec4 m_UVSourceRect;
		float m_DefaultXSize, m_DefaultYSize;
		GLuint m_VertexID, m_ProgramID;
	};
}

