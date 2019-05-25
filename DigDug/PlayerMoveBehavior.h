#pragma once
#include "State.h"
namespace dae
{
	class GridRenderComponent;
	class GameObject;
	class AnimationRenderComponent;
}

class PlayerMoveBehavior final : public dae::State
{
public:
	PlayerMoveBehavior(dae::GridRenderComponent* pGrid, dae::AnimationRenderComponent* pAnim);
	~PlayerMoveBehavior() = default;

	virtual int Update(dae::GameObject* pObj);
	virtual void Reset() override {} ;

	enum class Animation
	{
		RUNRIGHT, RUNLEFT, RUNUP, RUNDOWN, DIGRIGHT, DIGLEFT, DIGUP, DIGDOWN
	};
private:
	
	void RemoveTiles(dae::GameObject* pObj);
	bool CanMoveY(dae::GameObject* pObj);
	bool CanMoveX(dae::GameObject* pObj);
	dae::GridRenderComponent* m_pGrid;
	dae::AnimationRenderComponent* m_pAnim;

	void MoveLeft(dae::GameObject* pObj);
	void MoveRight(dae::GameObject* pObj);
	void MoveUp(dae::GameObject* pObj);
	void MoveDown(dae::GameObject* pObj);
	float tileSize = 5.0f;
	const float m_MoveSpeed;

	
};

