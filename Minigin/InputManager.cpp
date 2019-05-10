#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Action.h"
#include <algorithm>


bool dae::InputManager::ProcessInput()
{
	m_PrevButtonStates.erase(m_PrevButtonStates.begin(),m_PrevButtonStates.end());
	m_PrevButtonStates.insert(m_ButtonStates.begin(), m_ButtonStates.end());

	DWORD dwResult;
	for (DWORD i = 0; i < 1; i++)
	{
		memset(&m_State, 0, sizeof(XINPUT_STATE));

		// Simply get the state of the controllver from XInput.
		dwResult = XInputGetState(i, &m_State);
		std::for_each(m_ButtonStates.begin(), m_ButtonStates.end(), [this](std::pair<ControllerButton, bool> action)
		{
			if (IsPressed(action.first))m_ButtonStates[action.first] = true;
			else m_ButtonStates[action.first] = false; 
		});
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	if (m_State.Gamepad.wButtons & WORD(button)) return true;
	else return false;
}
void dae::InputManager::Assignbutton(const std::string& actionName, ControllerButton button)
{
	m_ButtonNames[actionName] = button;
}

bool dae::InputManager::GetButton(const std::string& action)
{
	return m_ButtonStates[m_ButtonNames[action]];
}

bool dae::InputManager::GetButtonDown(const std::string& action)
{
	return m_ButtonStates[m_ButtonNames[action]] && !m_PrevButtonStates[m_ButtonNames[action]];
}

bool dae::InputManager::GetButtonUp(const std::string& action)
{
	return !m_ButtonStates[m_ButtonNames[action]] && m_PrevButtonStates[m_ButtonNames[action]];
}