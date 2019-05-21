#pragma once
#include "GameObject.h"
namespace dae
{
	class GridRenderComponent;
}

class Player
{
public:
	Player() = delete;
	~Player() = default;
	static dae::GameObject* CreatePlayer(dae::GridRenderComponent* pGrid);
};

