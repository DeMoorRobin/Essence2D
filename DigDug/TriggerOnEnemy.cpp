#include "pch.h"
#include "TriggerOnEnemy.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"
#include "Inflatable.h"
#include "PlayerPumpState.h"

TriggerOnEnemy::TriggerOnEnemy(PlayerPumpState * pPumpState)
	:m_pPumpState{pPumpState}
{
}

void TriggerOnEnemy::Update(dae::CollisionBoxComponent * )
{
}

void TriggerOnEnemy::Execute(dae::CollisionBoxComponent * pOther, dae::CollisionBoxComponent * )
{
	auto* inflate = pOther->GetGameObject()->GetComponent<Inflatable*>();
	if (inflate)
	{
		m_pPumpState->SetHitEnemey();
		//trigger inflate as well
		inflate->RequestInflate();
	}
		
}
