#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Scene.h"

dae::GameObject::GameObject()
	:m_pComponents{}
{
	m_pTransform = new TransformComponent{};
	m_pTransform->SetGameObject(this);
}


dae::GameObject::~GameObject()
{
	//
	for (BaseComponent* pComponent : m_pComponents)
	{
		delete pComponent;
	}	
	m_pComponents.clear();
	delete m_pTransform;
}


void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	if (pComp->RequiresRenderComponent())
	{
		if (m_pRenderComponent)
		{
			std::cout << "An object may only have one rendering component\n";
			return;
		}			
		else
		{
			if (!m_pScene)
			{
				std::cout << "Add to scene before adding rendercomps\n";
				return;
			}
			m_pRenderComponent = m_pScene->RequestRenderComponent(this);
		}
	}
	m_pComponents.push_back(pComp);
	pComp->SetGameObject(this);
	pComp->Initialize();
}

void dae::GameObject::RelinkComponents()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->SetGameObject(this);
	}
	m_pTransform->SetGameObject(this);
}

void dae::GameObject::BaseUpdate()
{
	if (m_pRenderComponent) m_pRenderComponent->SetTransform(m_pTransform); 
	//for (BaseComponent* pComponent : m_pComponents)
	//{
	//	if(pComponent)
	//		pComponent->Update();
	//}
	for (size_t i{}; i < m_pComponents.size(); ++i)
	{
		if (m_pComponents[i])
			m_pComponents[i]->Update();
	}

}
void dae::GameObject::BaseDraw()
{
		
}
