#pragma once
#include "BaseComponent.h"
#include "StateMachineComponent.h"
#include "PookaInflate.h"

class Inflatable : public dae::BaseComponent
{
public:
	Inflatable(dae::StateMachineComponent* pSM,PookaInflate* pPooka, int inflateID) : m_pStateMachine{ pSM }, m_InflateID{inflateID},m_pPooka{pPooka}
	{};
	~Inflatable() = default;

	void RequestInflate() { m_pStateMachine->RequestState(m_InflateID); m_pPooka->Inflate(); };

	void Initialize() {};
	void Update() {};
private:
	dae::StateMachineComponent* m_pStateMachine;
	PookaInflate* m_pPooka;
	int m_InflateID;
};

