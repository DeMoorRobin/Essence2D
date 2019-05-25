#include "pch.h"
#include "PookaWander.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GridHelper.h"
#include "GridRenderComponent.h"
#include "Time.h"
#include "Pooka.h"


PookaWander::PookaWander(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2 )
	:PookaMoveBehavior{pGrid,size,moveSpeed,pPlayer1,pPlayer2}
	,m_TurnCooldown{0.1f}
	,m_TimeSinceLastTurn{}
{
}

int PookaWander::Update(dae::GameObject * pObj)
{
	if(SearchForPlayer(pObj, m_pPlayer1))
		return int(Pooka::PookaState::CHASE);
	if (m_pPlayer2)
		if(SearchForPlayer(pObj,m_pPlayer2))
			return int(Pooka::PookaState::CHASE);

	if (m_LastDirection == Direction::NONE )
	{
		m_LastDirection = ChooseRandomDirection(pObj);
		m_TimeSinceLastTurn = 0;
	}

	float euh = float(dae::Time::GetInstance().GetDeltaTime());
	if (euh > 0.016f) euh = 0.016f;
	m_TimeSinceLastTurn += euh;


	if (m_TimeSinceLastTurn >= m_TurnCooldown  && IsOnCross(pObj))
	{
		int testCount = 7;
		Direction newDir = ChooseRandomDirection(pObj);
		while (int(newDir) + int(m_LastDirection) == 3 && (testCount > 0))
		{
			newDir = ChooseRandomDirection(pObj);
			--testCount;
		}
		m_LastDirection = newDir;
		m_TimeSinceLastTurn = 0;
	}

	
	switch (m_LastDirection)
	{
	case PookaWander::Direction::UP:
		if(CanMoveUp(pObj))
			pObj->GetTransform()->Translate(0, m_MoveSpeed *euh, 0);
		else m_LastDirection = Direction::NONE;
		break;
	case PookaWander::Direction::DOWN:
		if (CanMoveDown(pObj))
			pObj->GetTransform()->Translate(0, -m_MoveSpeed * euh, 0);
		else m_LastDirection = Direction::NONE;
		break;
	case PookaWander::Direction::LEFT:
		if (CanMoveLeft(pObj))
			pObj->GetTransform()->Translate(-m_MoveSpeed * euh, 0, 0);
		else m_LastDirection = Direction::NONE;
		break;
	case PookaWander::Direction::RIGHT:
		if (CanMoveRight(pObj))
			pObj->GetTransform()->Translate(m_MoveSpeed * euh, 0, 0);
		else m_LastDirection = Direction::NONE;
		break;
	default:
		break;
	}

	return int(Pooka::PookaState::WANDER);
}

void PookaWander::Reset()
{
	m_LastDirection = Direction::NONE;
}
