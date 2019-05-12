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
	delete m_pRenderComponent;
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
	if (m_pRenderComponent)
	{
		if (m_pTransform->HasChanged())
			m_pRenderComponent->SetTransform(m_pTransform);

		m_pRenderComponent->Draw();
	}
	m_pTransform->ResetChanged();
}

void dae::GameObject::AddRenderComponent(RenderComponent* pRenderComponent)
{
	if (!m_pRenderComponent)
		m_pRenderComponent = pRenderComponent;
	else
		std::cout << "This object already has a renderComponent" << std::endl;
}