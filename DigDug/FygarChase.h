#pragma once
#include "FygarMoveBehavior.h"
namespace dae
{
	class GridRenderComponent;
	class AnimationRenderComponent;
	class GameObject;
}
class FygarChase final : public FygarMoveBehavior
{
public:
	FygarChase(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2, dae::AnimationRenderComponent* pAnim);
	~FygarChase();

	int Update(dae::GameObject* pObj) override;
	void Reset() override;

private:
	bool m_CurrentlySeesPlayer;
	glm::vec2 m_LastSpottedLocation;

	bool GoToLocation(dae::GameObject* pObj);
};

