#pragma once
#include "BaseComponent.h"
struct Vertex
{
	GLfloat x, y, z;
	GLfloat u, v;
};
namespace dae
{
	class GridRenderComponent final : public BaseComponent
	{
	public:
		GridRenderComponent(const std::string& textureFile, int rows, int columns);
		~GridRenderComponent();
	protected:
		void Initialize() override;
		void Update() override;
	private:
		std::string m_TextureFile;
		int m_Rows, m_Columns;
		GLuint m_VertexID, m_IndexID;

	};


}
