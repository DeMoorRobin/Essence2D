#include "MiniginPCH.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GridHelper.h"
#include "Time.h"
#include "Physics.h"
#include "CollisionCommand.h"

dae::CollisionBoxComponent::CollisionBoxComponent(int sizeX, int sizeY, bool isStatic, bool isTrigger)
	:BaseComponent{}
	,m_SizeX{sizeX}
	,m_SizeY{sizeY}
	,m_CurrentRect{}
	,m_IsStatic{isStatic}
	,m_IsTrigger{isTrigger}
	,m_pCommands{}
{
}

dae::CollisionBoxComponent::~CollisionBoxComponent()
{
	for (auto* command : m_pCommands)
	{
		delete command;
	}
	dae::Physics::GetInstance().RemoveCollisionComponent(this);
}


void dae::CollisionBoxComponent::TriggerCollision(CollisionBoxComponent * pOther)
{
	for (auto* command : m_pCommands)
	{
		command->Execute(pOther,this);
	}
}

void dae::CollisionBoxComponent::PrepareCollision()
{
	for (size_t i{}; i < m_pCommands.size(); ++i)
	{
		m_pCommands[i]->Update(this);
	}
}

void dae::CollisionBoxComponent::ClearCommands()
{
	for (auto* command : m_pCommands)
	{
		delete command;
	}
	m_pCommands.clear();
}

void dae::CollisionBoxComponent::Initialize()
{
	m_CurrentRect.x = dae::GridHelper::GetTileX(m_pGameObject->GetTransform()->GetPosition().x ) - m_SizeX/2;
	m_CurrentRect.y = dae::GridHelper::GetTileY(m_pGameObject->GetTransform()->GetPosition().y ) - m_SizeY/2;
	m_CurrentRect.w = m_SizeX;
	m_CurrentRect.h = m_SizeY;

	dae::Physics::GetInstance().AddCollisionComponent(this);
}

void dae::CollisionBoxComponent::Update()
{

	if (true)
	{
		m_CurrentRect.x = dae::GridHelper::GetTileX(m_pGameObject->GetTransform()->GetPosition().x) - m_SizeX / 2;
		m_CurrentRect.y = dae::GridHelper::GetTileY(m_pGameObject->GetTransform()->GetPosition().y) - m_SizeY / 2;
		m_CurrentRect.w = m_SizeX;
		m_CurrentRect.h = m_SizeY;
	}
}

