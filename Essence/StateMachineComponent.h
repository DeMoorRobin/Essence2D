#pragma once
#include "BaseComponent.h"
namespace dae
{
	class State;
	class StateMachineComponent final : public BaseComponent
	{
	public:
		StateMachineComponent(int startState);
		~StateMachineComponent();

		void SetStateVector(const std::vector<State*>& states) { m_pStates = states; };
		void Initialize() override;
		void Update() override;

		void RequestState(int id);

	private:
		std::vector<State*> m_pStates;
		int m_CurrentState;
	};
}

