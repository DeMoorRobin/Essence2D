#pragma once
#include "State.h"
namespace dae
{
	class AnimationRenderComponent;
	class GameObject;
	class Observer;
}
class PookaInflate final : public dae::State
{
public:
	PookaInflate(dae::AnimationRenderComponent* pAnim, dae::Observer* pObserver);
	~PookaInflate() = default;

	void Inflate() { m_WasPumped = true; };

	int Update(dae::GameObject* pObj) override;
	void Reset() override;
private:
	bool m_WasPumped;
	float m_InflateTime;
	dae::AnimationRenderComponent* m_pAnim;
	dae::Observer* m_pObserver;
};

