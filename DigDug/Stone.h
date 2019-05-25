#pragma once
namespace dae
{
	class GameObject;
	class GridRenderComponent;
	class Scene;
}
class Stone
{
public:
	Stone() = delete;
	~Stone() = default;
	static dae::GameObject* CreateStone(dae::GridRenderComponent* pGrid, dae::Scene* pScene);
};

