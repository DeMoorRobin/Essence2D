#include "pch.h"
#include "StoneBehavior.h"
#include "GridRenderComponent.h"
#include "GridHelper.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Time.h"
#include "CollisionBoxComponent.h"
#include "BlockOnPlayer.h"
#include "Scene.h"
#include "Squish.h"

StoneBehavior::StoneBehavior(dae::GridRenderComponent* pGrid, dae::CollisionBoxComponent* pCollision)
	:dae::BaseComponent{}
	,m_pGrid{pGrid}
	,m_State{State::STATIC}
	,m_pCollision{pCollision}
	,m_WaitTimer{}
{
}


StoneBehavior::~StoneBehavior()
{
}

void StoneBehavior::Initialize()
{

	float tileSize = 5.0f;
	for (int i{ -2 }; i < 3; ++i)
	{
		for (int j{ -2 }; j < 3; ++j)
		{
			GLuint tile = dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x + j * tileSize, m_pGameObject->GetTransform()->GetPosition().y + i * tileSize);
			m_pGrid->SetTileId(tile, 999);
		}
	}
}

void StoneBehavior::Update()
{
	//i chose to do this one without states because it is a simple flow from a -> b -> c -> d
	//state pattern would be an overkill imo
	switch (m_State)
	{
	case State::STATIC:
	{
		bool isNotClear = false;
		for (int i{ -2 }; i < 3; ++i)
		{
			auto tile = dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x - dae::GridHelper::GetTileSize()*i, m_pGameObject->GetTransform()->GetPosition().y - dae::GridHelper::GetTileSize() * 5);
			if (!m_pGrid->IsTileEmpty(tile))
				isNotClear = true;
		}
		if (!isNotClear)
		{
			m_State = State::WAIT;
			m_WaitTimer = 0.8f;
		}

	}
	break;
	case State::WAIT:
		m_ElapsedSec += float(dae::Time::GetInstance().GetDeltaTime());
		
		if (m_ElapsedSec >= m_WaitTimer)
		{
			m_State = State::CHECKFORPLAYER;
			m_pCollision->AddCommand(new BlockOnPlayer{ m_pGameObject->GetTransform()->GetPosition() });
			m_ElapsedSec = 0;
			m_IsPlayerUnderNeath = true;
		} 
		break;
	case State::CHECKFORPLAYER:
		if (!m_IsPlayerUnderNeath)
		{
			m_pCollision->EnableStatic(false);
			m_State = State::FALLING;
			m_pCollision->ClearCommands();
			m_pCollision->AddCommand(new Squish{});
			float tileSize = 5.0f;
			for (int i{ -2 }; i < 3; ++i)
			{
				for (int j{ -6 }; j < -3; ++j)
				{
					GLuint tile = dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x + i * tileSize, m_pGameObject->GetTransform()->GetPosition().y + j * tileSize);
					m_pGrid->SetTileId(tile, 999);
				}
			}
		}
			
		else m_IsPlayerUnderNeath = false;
		break;
	case State::FALLING:
		m_pGameObject->GetTransform()->Translate(0, float(-90.0*dae::Time::GetInstance().GetDeltaTime()), 0);
		{
			float tileSize = 5.0f;
			for (int i{ -2 }; i < 3; ++i)
			{
				for (int j{ -2 }; j < 3; ++j)
				{
					GLuint tile = dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x + j * tileSize, m_pGameObject->GetTransform()->GetPosition().y + i * tileSize);
					m_pGrid->SetTileId(tile, 999);
				}
			}
			bool isNotClear = false;
			for (int i{ -2 }; i < 3; ++i)
			{
				auto tile = dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x - dae::GridHelper::GetTileSize()*i, m_pGameObject->GetTransform()->GetPosition().y - dae::GridHelper::GetTileSize() * 3);
				if (!m_pGrid->IsTileEmpty(tile))
					isNotClear = true;
			}
			if (isNotClear)
			{
				m_State = State::DESPAWNING;
				m_ElapsedSec = 0;
				m_pCollision->ClearCommands();

			}
		}
		break;
	case State::DESPAWNING:
		m_ElapsedSec += float(dae::Time::GetInstance().GetDeltaTime());
		if (m_ElapsedSec >= m_WaitTimer)
		{
			m_pGameObject->GetScene()->RemoveChild(m_pGameObject);
		}
		break;
	}

}