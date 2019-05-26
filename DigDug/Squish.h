#pragma once
#include "CollisionCommand.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"
#include "SquishAble.h"
class Squish final : public dae::CollisionCommand
{
public:
	Squish();
	~Squish() = default;

	void Update(dae::CollisionBoxComponent* ) override {};
	void Execute(dae::CollisionBoxComponent* pOther, dae::CollisionBoxComponent * pOwner) override;
};

