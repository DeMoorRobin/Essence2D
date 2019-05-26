#pragma once
#include "FygarMoveBehavior.h"
namespace dae
{
	class GridRenderComponent;
	class AnimationRenderComponent;
	class GameObject;
}
class FygarWander final : public FygarMoveBehavior
{
public:
	FygarWander(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPLayer2, dae::AnimationRenderComponent* pAnim);
	~FygarWander() = default;

	int Update(dae::GameObject* pObj) override;
	void Reset() override;

private:
	float m_TimeSinceLastTurn;
	const float m_TurnCooldown;
};

