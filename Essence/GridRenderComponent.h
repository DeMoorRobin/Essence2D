#pragma once
#include "BaseComponent.h"
struct Vertex
{
	GLfloat x, y, z;
	//GLint texID;
	GLint id;
};
namespace dae
{
	class GridRenderComponent final : public BaseComponent
	{
	public:
		GridRenderComponent(const std::string& textureFile, int rows, int columns);
		~GridRenderComponent();

		void SetTileId(GLuint index, GLuint id, bool checkSurroundings = false);


	protected:
		void Initialize() override;
		void Update() override;
	private:
		std::string m_TextureFile;
		int m_Rows, m_Columns;
		GLuint m_VertexID, m_IndexID, m_ProgramID;

		std::vector<Vertex> m_Vertices{};
		std::vector<GLuint> m_Indices{};

	};


}
