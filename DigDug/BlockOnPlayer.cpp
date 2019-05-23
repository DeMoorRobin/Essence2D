#include "pch.h"
#include "BlockOnPlayer.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PlayerBehavior.h"
#include "StoneBehavior.h"

BlockOnPlayer::BlockOnPlayer(const glm::vec3& initPos)
	:m_PrevPos{initPos}
{
}


BlockOnPlayer::~BlockOnPlayer()
{
}

void BlockOnPlayer::Update(dae::CollisionBoxComponent * pOwner)
{
	m_PrevPos = pOwner->GetGameObject()->GetTransform()->GetPosition();
}

void BlockOnPlayer::Execute(dae::CollisionBoxComponent * pOther, dae::CollisionBoxComponent * pOwner)
{
	if (pOther->GetGameObject()->GetComponent<PlayerBehavior*>())
	{
		pOwner->GetGameObject()->GetTransform()->SetPosition(m_PrevPos);
		pOwner->GetGameObject()->GetComponent<StoneBehavior*>()->SetPlayerUnderneath();
	}
}
