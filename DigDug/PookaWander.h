#pragma once
#include "PookaMoveBehavior.h"
namespace dae
{
	class GridRenderComponent;
	class GameObject;
}

class PookaWander final : public PookaMoveBehavior
{
public:
	PookaWander(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPLayer2 = nullptr);
	int Update(dae::GameObject* pObj) override;
	void Reset() override;
	
private:
	float m_TimeSinceLastTurn;
	const float m_TurnCooldown;

};


