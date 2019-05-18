#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
	:m_Children{}
	,m_pComponents{}
{
	m_pTransform = new TransformComponent{};
}


dae::GameObject::~GameObject()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		delete pComponent;
	}
	delete m_pTransform;
}


void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	if (pComp->RequiresRenderComponent() && !m_pRenderComponent)
	{
		std::cout << "This component requires a renderComponent";
		return;
	}
	m_pComponents.push_back(pComp);
	pComp->SetGameObject(this);
	pComp->Initialize();
}

void dae::GameObject::BaseUpdate()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}
void dae::GameObject::BaseDraw()
{
		
}

void dae::GameObject::AddRenderComponent(RenderComponent* pRenderComponent)
{
	if (!m_pRenderComponent)
	{
		m_pRenderComponent = pRenderComponent;
		pRenderComponent->SetTransform(m_pTransform);
	}
		
	else
		std::cout << "This object already has a renderComponent" << std::endl;
}