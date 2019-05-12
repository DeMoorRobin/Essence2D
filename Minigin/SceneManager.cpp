#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

dae::SceneManager::SceneManager()
{
}


dae::SceneManager::~SceneManager()
{
	delete m_pActiveScene;
}


void dae::SceneManager::AddScene(Scene* pScene)
{
	//for now
	m_pActiveScene = pScene;
}
dae::Scene* dae::SceneManager::GetActiveScene()
{
	return m_pActiveScene;
}

void dae::SceneManager::BaseUpdate()
{
	m_pActiveScene->BaseUpdate();
}

void dae::SceneManager::BaseDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_pActiveScene->BaseDraw();
}