#pragma once
#include "BaseComponent.h"
namespace dae
{
	class GridRenderComponent;
	class AnimationRenderComponent;
}


class PlayerBehavior final : public dae::BaseComponent
{
public:
	PlayerBehavior(dae::GridRenderComponent* pGrid, dae::AnimationRenderComponent* pAnim);
	~PlayerBehavior() = default;
protected:
	void Initialize() override;
	void Update() override;
private:
	void RemoveTiles();
	bool CanMoveY();
	bool CanMoveX();
	GLuint GetTileX(float x);
	GLuint GetTileY(float y);
	GLuint GetTile(float x, float y);
	dae::GridRenderComponent* m_pGrid;
	dae::AnimationRenderComponent* m_pAnim;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	float tileSize = 5.0f;
	const float m_MoveSpeed;

	enum class Animation
	{
		RUNRIGHT,RUNLEFT,RUNUP,RUNDOWN, DIGRIGHT,DIGLEFT,DIGUP,DIGDOWN
	};

};

