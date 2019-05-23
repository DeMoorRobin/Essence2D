#pragma once
#include "BaseComponent.h"
namespace dae
{
	class GridRenderComponent;
	class CollisionBoxComponent;
}
class StoneBehavior final : public dae::BaseComponent
{
public:
	StoneBehavior(dae::GridRenderComponent* pGrid, dae::CollisionBoxComponent* pCollision);
	~StoneBehavior();
	void SetPlayerUnderneath() { m_IsPlayerUnderNeath = true; };

protected:
	void Initialize() override;
	void Update() override;
private:
	dae::GridRenderComponent* m_pGrid;
	dae::CollisionBoxComponent* m_pCollision;
	bool m_IsPlayerUnderNeath;
	float m_ElapsedSec;
	float m_WaitTimer;
	enum class State
	{
		STATIC, CHECKFORPLAYER,WAIT, FALLING, DESPAWNING
	};
	State m_State;
};

