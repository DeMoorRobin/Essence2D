#include "pch.h"
#include "SquishState.h"
#include "GameObject.h"
#include "AnimationRenderComponent.h"
#include "Pooka.h"
#include "Time.h"
#include "Scene.h"
#include "Observer.h"


SquishState::SquishState(dae::Scene * pScene, dae::AnimationRenderComponent * pAnim, dae::Observer* pObserver)
	:dae::State{}
	,m_pAnim{pAnim}
	,m_pScene{pScene}
	,m_AliveTime{}
	, m_pObserver{pObserver}
{
}

int SquishState::Update(dae::GameObject * pObj)
{
	m_AliveTime += float(dae::Time::GetInstance().GetDeltaTime());
	if (m_AliveTime >= 0.7f)
	{
		m_pObserver->OnNotify(pObj, dae::Event::ENEMY_SQUISHED);
		m_pScene->RemoveChild(pObj);	
	}

	return int(Pooka::PookaState::SQUISH);
}

void SquishState::Reset()
{
}
