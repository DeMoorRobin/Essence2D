#pragma once
#include "State.h"
namespace dae
{
	class Scene;
	class GameObject;
	class AnimationRenderComponent;
	class Observer;
}
class SquishState final : public dae::State
{
public:
	SquishState(dae::Scene* pScene, dae::AnimationRenderComponent* pAnim, dae::Observer* pObserver);
	~SquishState() = default;

	int Update(dae::GameObject* pObj) override;
	void Reset() override;
private:
	dae::AnimationRenderComponent* m_pAnim;
	dae::Scene* m_pScene;
	dae::Observer* m_pObserver;
	float m_AliveTime;
};

