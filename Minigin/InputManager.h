#pragma once
#include <XInput.h>
#include <unordered_map>
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Action;
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool GetButton(const std::string& action);
		bool GetButtonDown(const std::string& action);
		bool GetButtonUp(const std::string& action);

		void Assignbutton(const std::string& actionName, ControllerButton button);
	private:
		bool IsPressed(ControllerButton button) const;

		XINPUT_STATE m_State;
		std::unordered_map<std::string, ControllerButton> m_ButtonNames;
		std::unordered_map<ControllerButton, bool> m_ButtonStates;
		std::unordered_map<ControllerButton, bool> m_PrevButtonStates;
	};


}

