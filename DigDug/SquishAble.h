#pragma once
#include "BaseComponent.h"
#include "AnimationRenderComponent.h"
#include "StateMachineComponent.h"

class SquishAble final : public dae::BaseComponent
{
public:
	SquishAble(dae::StateMachineComponent* pSM, int stateID)
		:m_pSM{ pSM }, m_StateID{ stateID }, m_WasSquished{}
	{	}
	~SquishAble() = default;

	void SetSquished() { m_WasSquished = true; };

	void Initialize() override {};
	void Update() override { if (m_WasSquished)m_pSM->RequestState(m_StateID); };
private:
	dae::StateMachineComponent* m_pSM;
	int m_AnimID, m_StateID;

	bool m_WasSquished;
};

