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
	:BaseComponent{}
	,m_pGrid{pGrid}
	,m_MoveSpeed{60.0f}
	,m_pAnim{pAnim}
{
}

void PlayerBehavior::Initialize()
{
	std::vector<dae::Frame>* runRight{ new std::vector<dae::Frame>{} };
	runRight->push_back(dae::Frame{ 0, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	runRight->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* runLeft{ new std::vector<dae::Frame>{} };
	runLeft->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	runLeft->push_back(dae::Frame{ 64.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* runUp{ new std::vector<dae::Frame>{} };
	runUp->push_back(dae::Frame{ 0.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	runUp->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* runDown{ new std::vector<dae::Frame>{} };
	runDown->push_back(dae::Frame{ 0.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	runDown->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digRight{ new std::vector<dae::Frame> {} };
	digRight->push_back(dae::Frame{ 64.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digRight->push_back(dae::Frame{ 96.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digRight->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digRight->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digLeft{ new std::vector<dae::Frame> {} };
	digLeft->push_back(dae::Frame{ 96.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	digLeft->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	digLeft->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	digLeft->push_back(dae::Frame{ 192.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digUp{ new std::vector<dae::Frame> {} };
	digUp->push_back(dae::Frame{ 64.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digUp->push_back(dae::Frame{ 96.0f / 448.0f,  (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digUp->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digUp->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digDown{ new std::vector<dae::Frame> {} };
	digDown->push_back(dae::Frame{ 64.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digDown->push_back(dae::Frame{ 96.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digDown->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digDown->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	

	m_pAnim->AddAnimation(runRight, int(Animation::RUNRIGHT));
	m_pAnim->AddAnimation(runLeft, int(Animation::RUNLEFT));
	m_pAnim->AddAnimation(runUp, int(Animation::RUNUP));
	m_pAnim->AddAnimation(runDown, int(Animation::RUNDOWN));
	m_pAnim->AddAnimation(digRight, int(Animation::DIGRIGHT));
	m_pAnim->AddAnimation(digLeft, int(Animation::DIGLEFT));
	m_pAnim->AddAnimation(digUp, int(Animation::DIGUP));
	m_pAnim->AddAnimation(digDown, int(Animation::DIGDOWN));


	m_pAnim->SetCurrentAnimation(int(Animation::RUNRIGHT), 0.3f, 0, true);
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
	m_pGameObject->GetTransform()->Translate(-m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0, 0);

	GLuint checkTile{ dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x - 3.0f*tileSize, m_pGameObject->GetTransform()->GetPosition().y) };
	if(m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNLEFT), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGLEFT), 0.1f);
}

void PlayerBehavior::MoveRight()
{
	m_pGameObject->GetTransform()->Translate(m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0, 0);
	GLuint checkTile { dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x + 3.0f*tileSize, m_pGameObject->GetTransform()->GetPosition().y)};
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNRIGHT), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGRIGHT), 0.1f);
}

void PlayerBehavior::MoveUp()
{
	m_pGameObject->GetTransform()->Translate(0, m_MoveSpeed* dae::Time::GetInstance().GetDeltaTime(), 0);
	GLuint checkTile{ dae::GridHelper::GetTile(m_pGameObject->GetTransform()->GetPosition().x , m_pGameObject->GetTransform()->GetPosition().y + 3.0f*tileSize) };
	if (m_pGrid->IsTileEmpty(checkTile))
		m_pAnim->SetCurrentAnimation(int(Animation::RUNUP), 0.3f);
	else m_pAnim->SetCurrentAnimation(int(Animation::DIGUP), 0.1f);

}

void PlayerBehavior::MoveDown()
{
	m_pGameObject->GetTransform()->Translate(0, -m_MoveSpeed * dae::Time::GetInstance().GetDeltaTime(), 0);
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