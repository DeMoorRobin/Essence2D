#pragma once
#include "CollisionCommand.h"
class BlockOnPlayer final : public dae::CollisionCommand
{
public:
	BlockOnPlayer(const glm::vec3& initPos);
	~BlockOnPlayer();

	void Update(dae::CollisionBoxComponent* pOwner) override;
	void Execute(dae::CollisionBoxComponent* pOther, dae::CollisionBoxComponent * pOwner) override;
private:
	glm::vec3 m_PrevPos;
};

