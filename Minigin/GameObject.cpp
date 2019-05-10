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
	m_pComponents.push_back(pComp);
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
