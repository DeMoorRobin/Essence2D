#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include <algorithm>
#include "RenderComponent.h"

dae::Scene::Scene()
	:m_pChildren{ (std::vector<GameObject*>()) }
{
}


dae::Scene::~Scene()
{
	for (dae::GameObject* pObj : m_pChildren)
	{
		delete pObj;
	}

}


void dae::Scene::BaseUpdate()
{
	Update();
	//for (GameObject* pObj : m_pChildren)
	//{
	//	pObj->BaseUpdate();
	//}

	for (size_t i{}; i < m_pChildren.size(); ++i)
	{
		m_pChildren[i]->BaseUpdate();
	}
}

void dae::Scene::BaseDraw()
{
	auto er = glGetError();
	if (er != GL_NO_ERROR)
	{
		std::cout << er << std::endl;
	}
	std::sort(m_RenderComponents.begin(), m_RenderComponents.end(), [](dae::RenderComponent& a, dae::RenderComponent& b) {return a.GetDepth() < b.GetDepth(); });
	for (auto& render : m_RenderComponents)
	{
		render.Draw();
	}
	Draw();
}

void dae::Scene::AddChild(GameObject* pObj)
{
	pObj->SetScene(this);
	m_pChildren.push_back(pObj);
}

void dae::Scene::RemoveChild(GameObject * pObj)
{
	auto it2 = std::find(m_RenderComponents.begin(), m_RenderComponents.end(), *pObj->GetRenderComponent());
	if(it2 != m_RenderComponents.end())
		m_RenderComponents.erase(it2);

	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pObj);
	delete m_pChildren[it - m_pChildren.begin()];
	m_pChildren.erase(it);

	m_ObjToRenderMap.erase(pObj);
	for (auto* pObj : m_pChildren)
	{
		pObj->RelinkComponents();
	}
}

dae::RenderComponent* dae::Scene::RequestRenderComponent(dae::GameObject * pObj)
{
	m_RenderComponents.push_back(dae::RenderComponent{});
	m_RenderComponents.back().SetTransform(pObj->GetTransform());
	return &m_RenderComponents.back();
}