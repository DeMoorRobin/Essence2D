#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"

dae::Scene::Scene()
	:m_pChildren{ (std::vector<GameObject*>()) }
{
}


dae::Scene::~Scene()
{
	for (GameObject* pObj : m_pChildren)
	{
		delete pObj;
	}
}


void dae::Scene::BaseUpdate()
{
	Update();
	for (GameObject* pObj : m_pChildren)
	{
		pObj->BaseUpdate();
	}
}

void dae::Scene::BaseDraw()
{
	//for (GameObject* pObj : m_pChildren)
	//{
	//	pObj->BaseDraw();
	//}
	dae::Renderer::GetInstance().Draw();
	Draw();
}

void dae::Scene::AddChild(GameObject* Obj)
{
	m_pChildren.push_back(Obj);
}