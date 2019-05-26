#include "pch.h"
#include "PlayerBehavior.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Time.h"
#include "GridRenderComponent.h"
#include "AnimationRenderComponent.h"
#include "GridHelper.h"

PlayerBehavior::PlayerBehavior(dae::GridRenderComponent* pGrid, dae::AnimationRenderComponent* pAnim)
	:dae::BaseComponent{}
	,m_pGrid{pGrid}
	,m_MoveSpeed{60.0f}
	,m_pAnim{pAnim}
{
}

void PlayerBehavior::Initialize()
{
	
}

void PlayerBehavior::Update()
{
	//if (dae::InputManager::GetInstance().GetButton("A"))
	//{
	//	std::cout << "A" << std::endl;
	//}
	//if (dae::InputManager::GetInstance().GetButtonDown("BDown"))
	//{
	//	std::cout << "BDown" << std::endl;
	//}
	//if (dae::InputManager::GetInstance().GetButtonUp("XUp"))
	//{
	//	std::cout << "XUp" << std::endl;
	//}

	if (dae::InputManager::GetInstance().GetButton("Down"))
	{
		if (CanMoveY())
			MoveDown();
		else
		{
			auto x = dae::GridHelper::GetTileX(m_pGameObject->GetTransform()->GetPosition().x);
			if ((x - 3) % 7 < 4)
				MoveLeft();
			else MoveRight();
		}
	}
	if (dae::InputManager::GetInstance().GetButton("Up"))
	{
		if (CanMoveY())
			MoveUp();
		else
		{
			auto x = dae::GridHelper::GetTileX(m_pGameObject->GetTransform()->GetPosition().x);
			if ((x - 3) % 7 < 4)
				MoveLeft();
			else MoveRight();
		}

	}
	if (dae::InputManager::GetInstance().GetButton("Right"))
	{
		if (CanMoveX())
			MoveRight();
		else
		{
			auto y = dae::GridHelper::GetTileY(m_pGameObject->GetTransform()->GetPosition().y);
			if ((y - 3) % 7 < 4)
				MoveDown();
			else MoveUp();
		}
	}
	if (dae::InputManager::GetInstance().GetButton("Left"))
	{
		if (CanMoveX())
			MoveLeft();
		else
		{
			auto y = dae::GridHelper::GetTileY(m_pGameObject->GetTransform()->GetPosition().y);
			if ((y - 3) % 7 < 4)
				MoveDown();
			else MoveUp();
		}
	}

	RemoveTiles();
}

bool PlayerBehavior::CanMoveX()
{
	return (dae::GridHelper::GetTileY(m_pGameObject->GetTransform()->GetPosition().y) - 3) % 7 == 0;
}

bool PlayerBehavior::CanMoveY()
{
	return (dae::GridHelper::GetTileX(m_pGameObject->GetTransform()->GetPosition().x) - 3) % 7 == 0;
}

void PlayerBehavior::MoveLeft()
{
	m_pGameObject->GetTransform()->Translate(float(-m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime()), 0, 0);

	GLuint checkTile{ dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x - 3.0f*tileSize, m_pGameObject->GetTransform()->GetPosition().y) };
	if(m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNLEFT), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGLEFT), 0.1f);
}

void PlayerBehavior::MoveRight()
{
	m_pGameObject->GetTransform()->Translate(float(m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime()), 0, 0);
	GLuint checkTile { dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x + 3.0f*tileSize, m_pGameObject->GetTransform()->GetPosition().y)};
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNRIGHT), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGRIGHT), 0.1f);
}

void PlayerBehavior::MoveUp()
{
	m_pGameObject->GetTransform()->Translate(0,float( m_MoveSpeed* dae::Time::GetInstance().GetDeltaTime()), 0);
	GLuint checkTile{ dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x , m_pGameObject->GetTransform()->GetPosition().y + 3.0f*tileSize) };
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNUP), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGUP), 0.1f);

}

void PlayerBehavior::MoveDown()
{
	m_pGameObject->GetTransform()->Translate(0, float(-m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime()), 0);
	GLuint checkTile { dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x, m_pGameObject->GetTransform()->GetPosition().y - 3.0f*tileSize)};
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNDOWN), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGDOWN), 0.1f);
}

void PlayerBehavior::RemoveTiles()
{
	float tileSize = 5.0f;
	for (int i{ -2 }; i < 3; ++i)
	{
		for (int j{ -2 }; j < 3; ++j)
		{
			GLuint tile = dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x + j * tileSize, m_pGameObject->GetTransform()->GetPosition().y + i * tileSize);
			m_pGrid->SetTileId(tile, 999);
		}
	}
}