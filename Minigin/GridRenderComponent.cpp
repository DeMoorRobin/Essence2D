#include "MiniginPCH.h"
#include "GridRenderComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

dae::GridRenderComponent::GridRenderComponent(const std::string& textureFile, int rows, int columns)
	:BaseComponent{true}
	,m_Rows{rows}
	,m_Columns{columns}
	,m_TextureFile{textureFile}
{
}


dae::GridRenderComponent::~GridRenderComponent()
{
}

void dae::GridRenderComponent::Initialize()
{

	std::vector<Vertex> vertices{};
	std::vector<GLuint> indices{};
	const GLfloat size{ 10.0f };
	//const int blocks{ 64 * 35 };
	const GLuint height{ GLuint(m_Rows) };
	const GLuint width{ GLuint(m_Columns) };
	for (GLuint i{}; i < height; ++i)
	{
		for (GLuint j{}; j < width; ++j)
		{
			Vertex a{};
			a.x = size * j;
			a.y = size * i;
			a.z = 0;
			a.u = 0.0f;
			a.v = 0.0f;

			vertices.push_back(a);

			a.x = size * (j + 1);
			a.y = size * i;
			a.z = 0;
			a.u = 1.0f;
			a.v = 0.0f;
			vertices.push_back(a);
			a.x = size * j;
			a.y = size * (i + 1);
			a.z = 0;
			a.u = 0.0f;
			a.v = 1.0f;
			vertices.push_back(a);
			a.x = size * (j + 1);
			a.y = size * (i + 1);
			a.z = 0;
			a.u = 1.0f;
			a.v = 1.0f;
			vertices.push_back(a);

			indices.push_back(i * width * 4 + j * 4);      //0
			indices.push_back(i * width * 4 + j * 4 + 2);   //2
			indices.push_back(i * width * 4 + j * 4 + 1);   //1

			indices.push_back(i * width * 4 + j * 4 + 2); //2
			indices.push_back(i * width * 4 + j * 4 + 3); //3
			indices.push_back(i * width * 4 + j * 4 + 1); //1
		}
	}

	//vertexBuffer
	glGenBuffers(1, &m_VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	//index buffer
	glGenBuffers(1, &m_IndexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	m_pGameObject->GetRenderComponent()->SetBuffers(m_VertexID, m_IndexID);
	auto m = GLuint(m_Columns*m_Rows * 6);
	m_pGameObject->GetRenderComponent()->SetIndexCount(m);
	m_pGameObject->GetRenderComponent()->SetSpriteBased(false);

	auto t = dae::ResourceManager::GetInstance().LoadTexture(m_TextureFile);
	m_pGameObject->GetRenderComponent()->SetTexture(t);
}

void dae::GridRenderComponent::Update()
{

}
