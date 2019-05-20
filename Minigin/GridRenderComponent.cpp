#include "MiniginPCH.h"
#include "GridRenderComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Time.h"

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

	const GLfloat size{ 10.0f };
	//const int blocks{ 64 * 35 };
	const GLuint height{ GLuint(m_Rows) };
	const GLuint width{ GLuint(m_Columns) };
	for (GLuint i{}; i < height; ++i)
	{
		for (GLuint j{}; j < width; ++j)
		{
			Vertex a{};
			a.x = size*j+size/2.0f;
			a.y = size*i+size/2.0f;
			a.z = 0;
			a.id = 2;
			m_Vertices.push_back(a);
		}
	}

	//vertexBuffer
	glGenBuffers(1, &m_VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data(), GL_DYNAMIC_DRAW);
	//index buffer
	//glGenBuffers(1, &m_IndexID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);

	m_pGameObject->GetRenderComponent()->SetBuffers(m_VertexID, m_IndexID);
	auto m = GLuint(m_Columns*m_Rows);
	m_pGameObject->GetRenderComponent()->SetIndexCount(m);
	m_pGameObject->GetRenderComponent()->SetProgram(dae::ResourceManager::GetInstance().LoadShaders("tileVS.glsl", "tilePS.glsl", "tileGS.glsl"));
	m_pGameObject->GetRenderComponent()->SetRenderType(dae::RenderType::GRID);
	auto t = dae::ResourceManager::GetInstance().LoadTexture(m_TextureFile);
	m_pGameObject->GetRenderComponent()->SetTexture(t);
}

void dae::GridRenderComponent::Update()
{
	auto ind{ Time::GetInstance().GetFrameCounter() % (m_Rows*m_Columns) };
	m_Vertices[ind].id = rand() % 4;
	//vertexBuffer
	//glGenBuffers(1, &m_VertexID);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data(), GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferSubData(GL_ARRAY_BUFFER, ind * sizeof(Vertex) + 12, 4, &m_Vertices[ind].id);

	//m_pGameObject->GetRenderComponent()->SetBuffers(m_VertexID, m_IndexID);
}
