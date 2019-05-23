#pragma once
#include "CollisionCommand.h"
namespace dae
{
	class BlockMovement final : public CollisionCommand
	{
	public:
		BlockMovement();
		~BlockMovement();

	protected:
		void Update(CollisionBoxComponent* pOwner) override;
		void Execute(CollisionBoxComponent* pOther, CollisionBoxComponent * pOwner) override;
	private:
		glm::vec3 m_PrevPos;
	};


}
