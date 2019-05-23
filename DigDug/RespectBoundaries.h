#pragma once
#include "CollisionCommand.h"
namespace dae
{
	class CollisionBoxComponent;
}

class RespectBoundaries final : public dae::CollisionCommand
{
public:
	RespectBoundaries(float left, float right, float bot, float top);
	~RespectBoundaries() = default;
	void Update(dae::CollisionBoxComponent* pOwner) override;
	void Execute(dae::CollisionBoxComponent* pOther, dae::CollisionBoxComponent * pOwner) override;

private:
	const float m_LeftB, m_RightB, m_DownB, m_UpB;
	glm::vec3 m_PrevPos;
};

