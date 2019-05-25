#pragma once
#include "PookaMoveBehavior.h"
namespace dae
{
	class GridRenderComponent;
	class GameObject;
}
class PookaChase final : public PookaMoveBehavior
{
public:
	PookaChase(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2);
	~PookaChase();

	int Update(dae::GameObject* pObj) override;
	void Reset() override;

private:
	bool m_CurrentlySeesPlayer;
	glm::vec2 m_LastSpottedLocation;

	bool GoToLocation(dae::GameObject* pObj);
};

