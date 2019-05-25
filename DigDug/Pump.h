#pragma once
#include "PlayerPumpState.h"
namespace dae
{
	class Scene;
	class GameObject;
}
class Pump
{
public:
	Pump() = delete;
	~Pump() = default;

	static dae::GameObject* CreatePump(dae::Scene* pScene, PlayerPumpState::Direction dir);
};

