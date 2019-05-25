#pragma once
#include "CollisionCommand.h"
class PlayerPumpState;
namespace dae
{
	class CollisionBoxComponent;
}
class TriggerOnEnemy final : public dae::CollisionCommand
{
public:
	TriggerOnEnemy(PlayerPumpState* pPumpState);
	~TriggerOnEnemy() = default;

	void Update(dae::CollisionBoxComponent* pOwner) override;
	void Execute(dae::CollisionBoxComponent* pOther, dae::CollisionBoxComponent* pOwener) override;
private:
	PlayerPumpState* m_pPumpState;
};

