#pragma once
#include "State.h"
namespace dae
{
	class AnimationRenderComponent;
	class GameObject;
}
class PookaInflate final : public dae::State
{
public:
	PookaInflate();
	~PookaInflate() = default;

	void Inflate() { m_WasPumped = true; };

	int Update(dae::GameObject* pObj) override;
	void Reset() override;
private:
	bool m_WasPumped;
	float m_InflateTime;
};

