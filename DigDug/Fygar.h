#pragma once
namespace dae
{
	class GameObject;
	class GridRenderComponent;
	class Scene;
	class Observer;
}
class Fygar
{
public:
	Fygar() = delete;
	~Fygar() = default;
	static dae::GameObject* CreateFygar(dae::GridRenderComponent* pGrid, dae::Scene* pScene,dae::Observer* pScoreObserver , dae::GameObject* pPlayer1, dae::GameObject* pPLayer2 = nullptr);
	enum class FygarState
	{
		WANDER = 0, CHASE = 1, INFLATE = 2, SQUISH = 3
	};
};

