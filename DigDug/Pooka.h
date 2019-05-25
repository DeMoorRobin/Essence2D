#pragma once
namespace dae
{
	class GameObject;
	class GridRenderComponent;
	class Scene;
}
class Pooka
{
public:
	Pooka() = delete;
	~Pooka() = default;
	static dae::GameObject* CreatePooka(dae::GridRenderComponent* pGrid,dae::Scene* pScene, dae::GameObject* pPlayer1, dae::GameObject* pPLayer2);
	enum class PookaState
	{
		WANDER = 0, CHASE = 1, INFLATE =2
	};
	
};

