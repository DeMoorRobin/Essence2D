#include "pch.h"
#include "FygarWander.h"
#include "Fygar.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GridHelper.h"
#include "GridRenderComponent.h"
#include "Time.h"

#include "AnimationRenderComponent.h"


FygarWander::FygarWander(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2, dae::AnimationRenderComponent* pAnim)
	:FygarMoveBehavior{ pGrid,size,moveSpeed,pPlayer1,pAnim,pPlayer2 }
	, m_TurnCooldown{ 0.1f }
	, m_TimeSinceLastTurn{}
{
}

int FygarWander::Update(dae::GameObject * pObj)
{
	m_pAnim->SetCurrentAnimation(0, 0.2f, 0);
	if (SearchForPlayer(pObj, m_pPlayer1))
		return int(Fygar::FygarState::CHASE);
	if (m_pPlayer2)
		if (SearchForPlayer(pObj, m_pPlayer2))
			return int(Fygar::FygarState::CHASE);

	if (m_LastDirection == Direction::NONE)
	{
		m_LastDirection = ChooseRandomDirection(pObj);
		m_TimeSinceLastTurn = 0;
	}

	float euh = float(dae::Time::GetInstance().GetDeltaTime());
	if (euh > 0.016f) euh = 0.016f;
	m_TimeSinceLastTurn += euh;


	if (m_TimeSinceLastTurn >= m_TurnCooldown && IsOnCross(pObj))
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
	case FygarWander::Direction::UP:
		if (CanMoveUp(pObj))
			pObj->GetTransform()->Translate(0, m_MoveSpeed *euh, 0);
		else m_LastDirection = Direction::NONE;
		break;
	case FygarWander::Direction::DOWN:
		if (CanMoveDown(pObj))
			pObj->GetTransform()->Translate(0, -m_MoveSpeed * euh, 0);
		else m_LastDirection = Direction::NONE;
		break;
	case FygarWander::Direction::LEFT:
		if (CanMoveLeft(pObj))
			pObj->GetTransform()->Translate(-m_MoveSpeed * euh, 0, 0);
		else m_LastDirection = Direction::NONE;
		break;
	case FygarWander::Direction::RIGHT:
		if (CanMoveRight(pObj))
			pObj->GetTransform()->Translate(m_MoveSpeed * euh, 0, 0);
		else m_LastDirection = Direction::NONE;
		break;
	default:
		break;
	}

	return int(Fygar::FygarState::WANDER);
}

void FygarWander::Reset()
{
	m_LastDirection = Direction::NONE;
}
