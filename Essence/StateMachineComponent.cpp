#include "MiniginPCH.h"
#include "StateMachineComponent.h"
#include "State.h"

dae::StateMachineComponent::StateMachineComponent(int startState)
	:BaseComponent{}
	,m_pStates{}
	, m_CurrentState{startState}
{
}


dae::StateMachineComponent::~StateMachineComponent()
{
	for (auto* pState : m_pStates)
	{
		delete pState;
	}
}

void dae::StateMachineComponent::Initialize()
{

}

void dae::StateMachineComponent::Update()
{
	int stateRequest = m_pStates[m_CurrentState]->Update(m_pGameObject);
	if (stateRequest != m_CurrentState && int(m_pStates.size()) > stateRequest)
	{
		m_pStates[m_CurrentState]->Reset();
		m_CurrentState = stateRequest;
	}
}

void dae::StateMachineComponent::RequestState(int id)
{
	if (id != m_CurrentState && int(m_pStates.size()) > id)
	{
		m_pStates[m_CurrentState]->Reset();
		m_CurrentState = id;
	}
}
