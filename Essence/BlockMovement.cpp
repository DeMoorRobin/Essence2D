#include "MiniginPCH.h"
#include "BlockMovement.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

dae::BlockMovement::BlockMovement()
	:CollisionCommand{}
	,m_PrevPos{}
{
}


dae::BlockMovement::~BlockMovement()
{

}

void dae::BlockMovement::Update(CollisionBoxComponent * pOwner)
{
	m_PrevPos = pOwner->GetGameObject()->GetTransform()->GetPosition();

}

void dae::BlockMovement::Execute(CollisionBoxComponent * pOther, CollisionBoxComponent * pOwner)
{
	if (pOther->IsStatic())
	{
 		pOwner->GetGameObject()->GetTransform()->SetPosition(m_PrevPos);
	}
}
