#include "pch.h"
#include "PookaChase.h"
#include "GridHelper.h"
#include "GridRenderComponent.h"
#include "GameObject.h"
#include "Pooka.h"
#include "TransformComponent.h"
#include "Time.h"


PookaChase::PookaChase(dae::GridRenderComponent * pGrid, float size, float moveSpeed, dae::GameObject * pPlayer1, dae::GameObject * pPlayer2)
	:PookaMoveBehavior{ pGrid,size,moveSpeed,pPlayer1,pPlayer2 }
	,m_CurrentlySeesPlayer{}
{
}

PookaChase::~PookaChase()
{
}

int PookaChase::Update(dae::GameObject * pObj)
{
	//after respotting player first continue to cross section and then chase.

	glm::vec2 startPos = pObj->GetTransform()->GetPosition();
	m_CurrentlySeesPlayer = SearchForPlayer(pObj, m_pPlayer1);
	if(m_CurrentlySeesPlayer)m_LastSpottedLocation = { m_pPlayer1->GetTransform()->GetPosition().x,m_pPlayer1->GetTransform()->GetPosition().y };

	if (!m_CurrentlySeesPlayer && m_pPlayer2)
	{
		m_CurrentlySeesPlayer = SearchForPlayer(pObj, m_pPlayer2);
		if(m_CurrentlySeesPlayer) m_LastSpottedLocation = { m_pPlayer2->GetTransform()->GetPosition().x,m_pPlayer2->GetTransform()->GetPosition().y };
	}

	m_LastSpottedLocation.x = dae::GridHelper::GetTileX(m_LastSpottedLocation.x)*dae::GridHelper::GetTileSize() + dae::GridHelper::GetTileSize() / 2.0f;
	m_LastSpottedLocation.y = dae::GridHelper::GetTileY(m_LastSpottedLocation.y)*dae::GridHelper::GetTileSize() + dae::GridHelper::GetTileSize() / 2.0f;

	if (abs(m_LastSpottedLocation.x - pObj->GetTransform()->GetPosition().x) > abs(m_LastSpottedLocation.y - pObj->GetTransform()->GetPosition().y))
	{
		m_LastSpottedLocation.y = pObj->GetTransform()->GetPosition().y;
	}
	else m_LastSpottedLocation.x = pObj->GetTransform()->GetPosition().x;


	if (GoToLocation(pObj))
		return int(Pooka::PookaState::WANDER);

	if (startPos.x == pObj->GetTransform()->GetPosition().x && startPos.y == pObj->GetTransform()->GetPosition().y)
		return int(Pooka::PookaState::WANDER);

	return int(Pooka::PookaState::CHASE);
}

void PookaChase::Reset()
{
}

bool PookaChase::GoToLocation(dae::GameObject* pObj)
{
	bool xReached{ false };
	bool yReached{ false };

	bool xFailed{ false };
	bool yFailed{ false };

	xReached = abs(m_LastSpottedLocation.x - pObj->GetTransform()->GetPosition().x) <= dae::GridHelper::GetTileSize() / 2.0f;
	yReached = abs(m_LastSpottedLocation.y - pObj->GetTransform()->GetPosition().y) <= dae::GridHelper::GetTileSize() / 2.0f;
	if (xReached && yReached) return true;
	if (!yReached)
	{
		if (m_LastSpottedLocation.y > pObj->GetTransform()->GetPosition().y)
		{
			if (CanMoveUp(pObj))
			{
				pObj->GetTransform()->Translate(0, m_MoveSpeed *dae::Time::GetInstance().GetDeltaTime(), 0);
				m_LastDirection = Direction::UP;
			}
				
			else xFailed = true;
		}
		else
		{
			if (CanMoveDown(pObj))
			{
				pObj->GetTransform()->Translate(0, -m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0);
				m_LastDirection = Direction::DOWN;
			}
				
			else xFailed = true;
		}
	}
	else if (!xReached)
	{
		if (m_LastSpottedLocation.x > pObj->GetTransform()->GetPosition().x)
		{
			if (CanMoveRight(pObj))
			{
				pObj->GetTransform()->Translate(m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0);
				m_LastDirection = Direction::RIGHT;
			}
				
			else yFailed = true;
		}
		else
		{
			if (CanMoveLeft(pObj))
			{
				pObj->GetTransform()->Translate(-m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0);
				m_LastDirection = Direction::LEFT;
			}
			else yFailed = true;
		}
	}
	if ((xFailed||yReached) && (yFailed||xReached)) return true;
	return false;
}
