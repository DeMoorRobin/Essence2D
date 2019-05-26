#include "pch.h"
#include "Squish.h"


Squish::Squish()
{
}

void Squish::Execute(dae::CollisionBoxComponent * pOther, dae::CollisionBoxComponent * pOwner)
{
	SquishAble* squishable{ pOther->GetGameObject()->GetComponent<SquishAble*>() };
	if (squishable)
	{
		squishable->SetSquished();
	}
}


