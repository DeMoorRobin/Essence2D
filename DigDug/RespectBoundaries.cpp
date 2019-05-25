#include "pch.h"
#include "RespectBoundaries.h"
#include "GridHelper.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
RespectBoundaries::RespectBoundaries(float left,float right, float bot, float top)
	:dae::CollisionCommand{}
	,m_LeftB{left}
	,m_RightB{right}
	,m_DownB{bot}
	,m_UpB{top}
{
}

void RespectBoundaries::Update(dae::CollisionBoxComponent * pOwner)
{
	auto& rect = pOwner->GetCurrentRect();
	if (rect.x <= m_LeftB || rect.x + rect.w >= m_RightB || rect.y <= m_DownB || rect.y + rect.h >= m_UpB)
		pOwner->GetGameObject()->GetTransform()->SetPosition(m_PrevPos);
	else m_PrevPos = pOwner->GetGameObject()->GetTransform()->GetPosition();
}

void RespectBoundaries::Execute(dae::CollisionBoxComponent * , dae::CollisionBoxComponent *)
{
}
