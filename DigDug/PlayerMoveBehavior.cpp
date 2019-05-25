#include "pch.h"
#include "PlayerMoveBehavior.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GridRenderComponent.h"
#include "GridHelper.h"
#include "AnimationRenderComponent.h"
#include "InputManager.h"
#include "Player.h"
#include "Time.h"

PlayerMoveBehavior::PlayerMoveBehavior(dae::GridRenderComponent* pGrid, dae::AnimationRenderComponent* pAnim)
	:dae::State{}
	, m_pGrid{ pGrid }
	, m_MoveSpeed{ 60.0f }
	, m_pAnim{ pAnim }
{
}

int PlayerMoveBehavior::Update(dae::GameObject * pObj)
{
	if (dae::InputManager::GetInstance().GetButtonDown("Pump"))
		return int(Player::PlayerState::Pumping);

	if (dae::InputManager::GetInstance().GetButton("Down"))
	{
		if (CanMoveY(pObj))
			MoveDown(pObj);
		else
		{
			auto x = dae::GridHelper::GetTileX(pObj->GetTransform()->GetPosition().x);
			if ((x - 3) % 7 < 4)
				MoveLeft(pObj);
			else MoveRight(pObj);
		}
	}
	if (dae::InputManager::GetInstance().GetButton("Up"))
	{
		if (CanMoveY(pObj))
			MoveUp(pObj);
		else
		{
			auto x = dae::GridHelper::GetTileX(pObj->GetTransform()->GetPosition().x);
			if ((x - 3) % 7 < 4)
				MoveLeft(pObj);
			else MoveRight(pObj);
		}

	}
	if (dae::InputManager::GetInstance().GetButton("Right"))
	{
		if (CanMoveX(pObj))
			MoveRight(pObj);
		else
		{
			auto y = dae::GridHelper::GetTileY(pObj->GetTransform()->GetPosition().y);
			if ((y - 3) % 7 < 4)
				MoveDown(pObj);
			else MoveUp(pObj);
		}
	}
	if (dae::InputManager::GetInstance().GetButton("Left"))
	{
		if (CanMoveX(pObj))
			MoveLeft(pObj);
		else
		{
			auto y = dae::GridHelper::GetTileY(pObj->GetTransform()->GetPosition().y);
			if ((y - 3) % 7 < 4)
				MoveDown(pObj);
			else MoveUp(pObj);
		}
	}
	RemoveTiles(pObj);

	return int(Player::PlayerState::Moving);
}

void PlayerMoveBehavior::RemoveTiles(dae::GameObject* pObj)
{
	float tileSize = 5.0f;
	for (int i{ -2 }; i < 3; ++i)
	{
		for (int j{ -2 }; j < 3; ++j)
		{
			GLuint tile = dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + j * tileSize, pObj->GetTransform()->GetPosition().y + i * tileSize);
			m_pGrid->SetTileId(tile, 999);
		}
	}
}

bool PlayerMoveBehavior::CanMoveY(dae::GameObject* pObj)
{
	return (dae::GridHelper::GetTileX(pObj->GetTransform()->GetPosition().x) - 3) % 7 == 0;
}

bool PlayerMoveBehavior::CanMoveX(dae::GameObject* pObj)
{
	return (dae::GridHelper::GetTileY(pObj->GetTransform()->GetPosition().y) - 3) % 7 == 0;
}

void PlayerMoveBehavior::MoveLeft(dae::GameObject* pObj)
{
	pObj->GetTransform()->Translate(-m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0, 0);

	GLuint checkTile{ dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - 3.0f*tileSize, pObj->GetTransform()->GetPosition().y) };
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNLEFT), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGLEFT), 0.1f);
}

void PlayerMoveBehavior::MoveRight(dae::GameObject* pObj)
{
	pObj->GetTransform()->Translate(m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0, 0);
	GLuint checkTile{ dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + 3.0f*tileSize, pObj->GetTransform()->GetPosition().y) };
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNRIGHT), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGRIGHT), 0.1f);
}

void PlayerMoveBehavior::MoveUp(dae::GameObject* pObj)
{
	pObj->GetTransform()->Translate(0, m_MoveSpeed* dae::Time::GetInstance().GetDeltaTime(), 0);
	GLuint checkTile{ dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x , pObj->GetTransform()->GetPosition().y + 3.0f*tileSize) };
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNUP), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGUP), 0.1f);
}

void PlayerMoveBehavior::MoveDown(dae::GameObject* pObj)
{
	pObj->GetTransform()->Translate(0, -m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0);
	GLuint checkTile{ dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x, pObj->GetTransform()->GetPosition().y - 3.0f*tileSize) };
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNDOWN), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGDOWN), 0.1f);
}


