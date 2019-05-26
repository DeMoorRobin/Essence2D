#include "MiniginPCH.h"
#include "Physics.h"
#include "CollisionBoxComponent.h"
#include "GridHelper.h"
#include <unordered_map>
#include <algorithm>

dae::Physics::Physics()
{
}


dae::Physics::~Physics()
{
}

void dae::Physics::AddCollisionComponent(dae::CollisionBoxComponent* pBox)
{
	m_pCollisionBoxes.push_back(pBox);
}

void dae::Physics::RemoveCollisionComponent(CollisionBoxComponent * pBox)
{
	auto it = std::find(m_pCollisionBoxes.begin(), m_pCollisionBoxes.end(), pBox);
	if(it!=m_pCollisionBoxes.end())
		m_pCollisionBoxes.erase(it);
}

void dae::Physics::Update()
{
	std::unordered_multimap<int, dae::CollisionBoxComponent*> collisionMap{};
	std::unordered_multimap<dae::CollisionBoxComponent*, dae::CollisionBoxComponent*> triggeredCollisions{};
	
	//build collision map

	//this puts the pointers to the collisionComponents as value with the tile it is on as key
	for (auto* box : m_pCollisionBoxes)
	{
		
		auto& tiles = box->GetCurrentRect();
		for (int i{}; i < tiles.h; ++i)
		{
			for (int j{}; j < tiles.w; ++j)
			{
				collisionMap.insert({ int(GridHelper::GetColumns())*(tiles.y + i) + tiles.x + j, box });
			}
		}
	}

	//loop over all tiles containing a collisionbox
	for (auto it = collisionMap.begin(), end = collisionMap.end(); it != end; it = collisionMap.upper_bound(it->first))
	{
		//if a tile points to more than 1 collisionbox there is a collision
		auto collisionCount = collisionMap.count(it->first);
		if (collisionMap.count(it->first) > 1)
		{
			auto itCopy = it;
			//add all boxcomponents that are on this specific tile to collisions.
			std::vector<dae::CollisionBoxComponent*> collisions{};
			std::for_each(it, collisionMap.upper_bound(it->first), [&collisions](const std::pair<int, dae::CollisionBoxComponent*>& a) {collisions.push_back(a.second); });
			
			for (size_t i{}; i < collisionCount; ++i)
			{
				for (size_t other{}; other < collisionCount; ++other)
				{
					if (other == i) continue;
					auto triggeredOnThisVal = triggeredCollisions.equal_range(collisions[i]);

					bool alreadyChecked = false;
					for (auto check = triggeredOnThisVal.first; check != triggeredOnThisVal.second; ++check)
					{
						if (check->second == collisions[other])
							alreadyChecked = true;
					}
					if (!alreadyChecked)
					{
						collisions[i]->TriggerCollision(collisions[other]);
						triggeredCollisions.insert({ collisions[i] , collisions[other] });
					}
					
				}
			}
	
		}
	}
	for (auto* box : m_pCollisionBoxes)
	{
		box->PrepareCollision();
	}

}