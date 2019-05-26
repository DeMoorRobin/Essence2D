#pragma once
namespace dae
{
	class GameObject;
	class GridRenderComponent;
	class Scene;
	class Observer;
}
class Pooka
{
public:
	Pooka() = delete;
	~Pooka() = default;
	static dae::GameObject* CreatePooka(dae::GridRenderComponent* pGrid,dae::Scene* pScene, dae::Observer* pScoreObserver, dae::GameObject* pPlayer1, dae::GameObject* pPLayer2 = nullptr);
	enum class PookaState
	{
		WANDER = 0, CHASE = 1, INFLATE =2, SQUISH =3
	};
	
};

