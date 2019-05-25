#include "pch.h"
#include "PookaMoveBehavior.h"
#include "GameObject.h"
#include "GridHelper.h"
#include "GridRenderComponent.h"
#include "TransformComponent.h"

PookaMoveBehavior::PookaMoveBehavior(dae::GridRenderComponent* pGrid, float size, float moveSpeed, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2)
	:m_LastDirection{ Direction::NONE }
	, m_pGrid{ pGrid }
	, m_HalfSizePlus{ size / 2.0f + dae::GridHelper::GetTileSize() / 3.0f }
	, m_HalfSize{ size / 2.5f }
	, m_MoveSpeed{ moveSpeed }
	, m_pPlayer1{ pPlayer1 }
	, m_pPlayer2{ pPlayer2 }
{
}



PookaMoveBehavior::Direction PookaMoveBehavior::ChooseRandomDirection(dae::GameObject * pObj)
{
	Direction startDir = Direction(rand() % 4);
	Direction checkDir = startDir;
	bool dirFree{};
	do
	{
		switch (checkDir)
		{
		case PookaMoveBehavior::Direction::UP:
			dirFree = CanMoveUp(pObj);
			break;
		case PookaMoveBehavior::Direction::DOWN:
			dirFree = CanMoveDown(pObj);
			break;
		case PookaMoveBehavior::Direction::LEFT:
			dirFree = CanMoveLeft(pObj);
			break;
		case PookaMoveBehavior::Direction::RIGHT:
			dirFree = CanMoveRight(pObj);
			break;
		default:
			break;
		}
		if (!dirFree)checkDir = Direction((int(checkDir) + 1) % 4);

	} while (!((startDir == checkDir) || (dirFree == true)));

	if (dirFree == false) return Direction::NONE;
	else return checkDir;
}

bool PookaMoveBehavior::SearchForPlayer(dae::GameObject * pObj, dae::GameObject* pPlayer)
{
	if (abs(pObj->GetTransform()->GetPosition().x - pPlayer->GetTransform()->GetPosition().x) <= dae::GridHelper::GetTileSize() / 2.0f)
	{
		if (pObj->GetTransform()->GetPosition().y > pPlayer->GetTransform()->GetPosition().y)
		{
			//search down
			auto x{ pObj->GetTransform()->GetPosition().x };
			auto yCheck{ pObj->GetTransform()->GetPosition().y };
			bool LOS{ true };
			while (yCheck >= pPlayer->GetTransform()->GetPosition().y && LOS)
			{
				LOS = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(x, yCheck));
				yCheck -= dae::GridHelper::GetTileSize();
			}
			if (LOS) return true;
			else return false;
		}
		else
		{
			//search up
			auto x{ pObj->GetTransform()->GetPosition().x };
			auto yCheck{ pObj->GetTransform()->GetPosition().y };
			bool LOS{ true };
			while (yCheck <= pPlayer->GetTransform()->GetPosition().y && LOS)
			{
				LOS = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(x, yCheck));
				yCheck += dae::GridHelper::GetTileSize();
			}
			if (LOS) return true;
			else return false;
		}
	}
	else if (abs(pObj->GetTransform()->GetPosition().y - pPlayer->GetTransform()->GetPosition().y) <= dae::GridHelper::GetTileSize() / 2.0f)
	{
		if (pObj->GetTransform()->GetPosition().x > pPlayer->GetTransform()->GetPosition().x)
		{
			//search left
			auto xCheck{ pObj->GetTransform()->GetPosition().x };
			auto y{ pObj->GetTransform()->GetPosition().y };
			bool LOS{ true };
			while (xCheck >= pPlayer->GetTransform()->GetPosition().x && LOS)
			{
				LOS = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(xCheck, y));
				xCheck -= dae::GridHelper::GetTileSize();
			}
			if (LOS) return true;
			else return false;
		}
		else
		{
			//search right
			auto xCheck{ pObj->GetTransform()->GetPosition().x };
			auto y{ pObj->GetTransform()->GetPosition().y };
			bool LOS{ true };
			while (xCheck <= pPlayer->GetTransform()->GetPosition().x && LOS)
			{
				LOS = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(xCheck, y));
				xCheck += dae::GridHelper::GetTileSize();
			}
			if (LOS) return true;
			else return false;
		}
	}
	else return false;
}

bool PookaMoveBehavior::CanMoveUp(dae::GameObject* pObj)
{
	bool leftUpFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSize, pObj->GetTransform()->GetPosition().y + m_HalfSizePlus));
	bool rightUpFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + m_HalfSize, pObj->GetTransform()->GetPosition().y + m_HalfSizePlus));
	//GLuint tileId = dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSize, pObj->GetTransform()->GetPosition().y + m_HalfSizePlus);
	//m_pGrid->SetTileId(tileId, 3);
	//tileId = dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + m_HalfSize, pObj->GetTransform()->GetPosition().y + m_HalfSizePlus);
	//m_pGrid->SetTileId(tileId, 3);

	//return m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x , pObj->GetTransform()->GetPosition().y + m_HalfSizePlus));
	return leftUpFree && rightUpFree;
}

bool PookaMoveBehavior::CanMoveLeft(dae::GameObject* pObj)
{
	//GLuint tileId = dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSizePlus, pObj->GetTransform()->GetPosition().y + m_HalfSizePlus);
	//m_pGrid->SetTileId(tileId, 3);
	//tileId = dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSizePlus, pObj->GetTransform()->GetPosition().y - m_HalfSizePlus);
	//m_pGrid->SetTileId(tileId, 3);

	bool leftUpFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSizePlus, pObj->GetTransform()->GetPosition().y + m_HalfSize));
	bool leftDownFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSizePlus, pObj->GetTransform()->GetPosition().y - m_HalfSize));
	return leftUpFree && leftDownFree;
	//return m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSizePlus, pObj->GetTransform()->GetPosition().y));
}

bool PookaMoveBehavior::CanMoveDown(dae::GameObject* pObj)
{
	bool leftDownFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x - m_HalfSize, pObj->GetTransform()->GetPosition().y - m_HalfSizePlus));
	bool rightDownFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + m_HalfSize, pObj->GetTransform()->GetPosition().y - m_HalfSizePlus));
	return leftDownFree && rightDownFree;
	//return  m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x , pObj->GetTransform()->GetPosition().y - m_HalfSizePlus));
}

bool PookaMoveBehavior::CanMoveRight(dae::GameObject* pObj)
{
	bool rightUpFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + m_HalfSizePlus, pObj->GetTransform()->GetPosition().y + m_HalfSize));
	bool rightDownFree = m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + m_HalfSizePlus, pObj->GetTransform()->GetPosition().y - m_HalfSize));
	return rightUpFree && rightDownFree;
	//return m_pGrid->IsTileEmpty(dae::GridHelper::GetTile(pObj->GetTransform()->GetPosition().x + m_HalfSizePlus, pObj->GetTransform()->GetPosition().y ));
}

bool PookaMoveBehavior::IsOnCross(dae::GameObject * pObj)
{
	return ((dae::GridHelper::GetTileY(pObj->GetTransform()->GetPosition().y) - 3) % 7 == 0)
		&& ((dae::GridHelper::GetTileX(pObj->GetTransform()->GetPosition().x) - 3) % 7 == 0);
}

