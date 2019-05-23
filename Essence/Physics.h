#pragma once
#include "Singleton.h"
namespace dae
{
	class CollisionBoxComponent;
	class Physics final : public Singleton<Physics>
	{
	public:
		Physics();
		~Physics();

		void AddCollisionComponent(CollisionBoxComponent* pBox);
		
		void Update();
	
	private:
		std::vector<CollisionBoxComponent*> m_pCollisionBoxes;
		
		
	};
}
