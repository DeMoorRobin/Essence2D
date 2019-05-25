#pragma once
#include "State.h"
namespace dae
{
	class Scene;
	class GameObject;
	class AnimationRenderComponent;
}
class PlayerPumpState final : public dae::State
{
public:
	PlayerPumpState(dae::Scene* pScene, dae::AnimationRenderComponent* pAnim);
	~PlayerPumpState();
	int Update(dae::GameObject* pObj) override;
	void Reset() override;
	void SetHitEnemey() { m_HasHitEnemy = true; };
	enum class Direction
	{
		RIGHT, LEFT, UP, DOWN
	};
private:
	dae::AnimationRenderComponent* m_pAnim;
	dae::Scene* m_pScene;
	Direction m_Direction;

	float m_PumpAliveTime, m_TimeSinceTrigger;

	bool m_HasSpawnedPump, m_HasHitEnemy;
	dae::GameObject* m_pPump;
	
};

