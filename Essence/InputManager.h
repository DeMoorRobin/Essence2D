#pragma once
#include <XInput.h>
#include <unordered_map>
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Action;
	enum class Button
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		DPadUp = XINPUT_GAMEPAD_DPAD_UP,
		DPadDown = XINPUT_GAMEPAD_DPAD_DOWN
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool GetButton(const std::string& action);
		bool GetButtonDown(const std::string& action);
		bool GetButtonUp(const std::string& action);

		void Assignbutton(const std::string& actionName, Button button);
	private:
		bool IsPressed(Button button) const;

		XINPUT_STATE m_State;
		std::unordered_map<std::string, Button> m_ButtonNames;
		std::unordered_map<Button, bool> m_ButtonStates;
		std::unordered_map<Button, bool> m_PrevButtonStates;
	};


}

