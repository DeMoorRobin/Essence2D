#include "pch.h"
#include "PlayerPumpState.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GridRenderComponent.h"
#include "GridHelper.h"
#include "AnimationRenderComponent.h"
#include "InputManager.h"
#include "Player.h"
#include "Time.h"
#include "Pump.h"
#include "Scene.h"
#include "CollisionBoxComponent.h"
#include "TriggerOnEnemy.h"

PlayerPumpState::PlayerPumpState(dae::Scene * pScene, dae::AnimationRenderComponent * pAnim)
	:dae::State{}
	,m_pAnim{pAnim}
	,m_pScene{pScene}
	,m_HasSpawnedPump{}
	,m_Direction{}
	,m_HasHitEnemy{false}
	,m_TimeSinceTrigger{}
{
}


PlayerPumpState::~PlayerPumpState()
{
}

int PlayerPumpState::Update(dae::GameObject * pObj)
{
	if(!m_HasSpawnedPump)
	{
		m_Direction = Direction(m_pAnim->GetCurrentAnimation() % 4);

		m_pPump = Pump::CreatePump(m_pScene,m_Direction);
		m_HasSpawnedPump = true;
		m_pPump->GetTransform()->SetPosition(pObj->GetTransform()->GetPosition());
		dae::CollisionBoxComponent* col{};
		switch (m_Direction)
		{
		case Direction::RIGHT:
		{
			m_pPump->GetTransform()->Translate(25.0f, 0.0f, 0.2f);
			col = new dae::CollisionBoxComponent{ 10,4,false,true };
			m_pPump->AddComponent(col);
		}
			break;
		case Direction::LEFT:
		{
			m_pPump->GetTransform()->Translate(-25.0f, 0, 0.2f);
			col = new dae::CollisionBoxComponent{ 10,4,false,true };
			m_pPump->AddComponent(col);
		}
			break;
		case Direction::DOWN:
		{
			m_pPump->GetTransform()->Translate(0, -25.0f, 0.2f);
			col = new dae::CollisionBoxComponent{ 4,10,false,true };
			m_pPump->AddComponent(col);
		}
			break;
		case Direction::UP:
		{
			m_pPump->GetTransform()->Translate(0, 25.0f, 0.2f);
			col = new dae::CollisionBoxComponent{ 4,10,false,true };
			m_pPump->AddComponent(col);
		}
			break;
		}
		col->AddCommand(new TriggerOnEnemy{ this });
		m_PumpAliveTime = 0;
	}

	if (m_HasHitEnemy)
	{
		m_HasHitEnemy = false;
		m_PumpAliveTime = 0;
	}

	m_PumpAliveTime += float(dae::Time::GetInstance().GetDeltaTime());
	if (m_PumpAliveTime > 0.5f || m_TimeSinceTrigger > 0.2f)
	{
		m_pScene->RemoveChild(m_pPump);
		m_pPump = nullptr;
		return int(Player::PlayerState::Moving);
	}

	m_TimeSinceTrigger += float(dae::Time::GetInstance().GetDeltaTime());
	if (dae::InputManager::GetInstance().GetButton("Pump"))
	{
		m_TimeSinceTrigger = 0;
	}


	return int(Player::PlayerState::Pumping);
}

void PlayerPumpState::Reset()
{
	if (m_pPump)
	{
		m_pScene->RemoveChild(m_pPump);
	}
	m_HasSpawnedPump = false;
	m_PumpAliveTime = 0;
	m_HasHitEnemy = false;
	m_TimeSinceTrigger = 0;

}
 