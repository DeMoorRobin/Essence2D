#pragma once
#include "GameObject.h"
namespace dae
{
	class GridRenderComponent;
	class Scene;
}

class Player
{
public:
	Player() = delete;
	~Player() = default;
	static dae::GameObject* CreatePlayer(dae::GridRenderComponent* pGrid, dae::Scene* pScene);

	enum class PlayerState
	{
		Moving,Pumping
	};
};

