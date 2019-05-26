#pragma once
#include "BaseComponent.h"
#include "StateMachineComponent.h"
#include "PookaInflate.h"
#include "FygarInflate.h"

class Inflatable : public dae::BaseComponent
{
public:
	Inflatable(dae::StateMachineComponent* pSM,PookaInflate* pPooka, FygarInflate* pFygar, int inflateID) : m_pStateMachine{ pSM }, m_InflateID{inflateID},m_pPooka{pPooka},m_pFygar{pFygar}
	{};
	~Inflatable() = default;

	void RequestInflate() { m_pStateMachine->RequestState(m_InflateID); if (m_pPooka)m_pPooka->Inflate(); else m_pFygar->Inflate(); };

	void Initialize() {};
	void Update() {};
private:
	dae::StateMachineComponent* m_pStateMachine;
	PookaInflate* m_pPooka;
	FygarInflate* m_pFygar;
	int m_InflateID;
};

