#pragma once
#include "State.h"
namespace dae
{
	class GridRenderComponent;
	class GameObject;
}
class PookaMoveBehavior : public dae::State
{
public:
	PookaMoveBehavior(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2);
	virtual ~PookaMoveBehavior() = default;

	virtual int Update(dae::GameObject* pObj) = 0;
	virtual void Reset() = 0;
protected:
	enum class Direction
	{
		UP, LEFT, RIGHT, DOWN, NONE
	};
	Direction m_LastDirection;
	dae::GridRenderComponent* m_pGrid;
	dae::GameObject* m_pPlayer1;
	dae::GameObject* m_pPlayer2;
	float m_MoveSpeed;
	const float m_HalfSizePlus; //halfsize + a tile
	const float m_HalfSize;
	Direction ChooseRandomDirection(dae::GameObject * pObj);

	bool SearchForPlayer(dae::GameObject* pObj, dae::GameObject* pPlayer);
	bool CanMoveUp(dae::GameObject* pObj);
	bool CanMoveLeft(dae::GameObject* pObj);
	bool CanMoveDown(dae::GameObject* pObj);
	bool CanMoveRight(dae::GameObject* pObj);
	bool IsOnCross(dae::GameObject* pObj);

};

