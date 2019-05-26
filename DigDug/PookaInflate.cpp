#include "pch.h"
#include "PookaInflate.h"
#include "Time.h"
#include "GameObject.h"
#include "Scene.h"
#include "Pooka.h"
#include "AnimationRenderComponent.h"
#include "TransformComponent.h"
#include "Observer.h"

PookaInflate::PookaInflate(dae::AnimationRenderComponent* pAnim, dae::Observer* pObserver)
	:m_InflateTime{}
	,m_WasPumped{}
	,m_pAnim{pAnim}
	,m_pObserver{pObserver}
{
}

int PookaInflate::Update(dae::GameObject * pObj)
{
	if (m_WasPumped)
	{
		m_InflateTime += dae::Time::GetInstance().GetDeltaTime();
		
		m_WasPumped = false;
	}
	else
	{
		m_InflateTime -= dae::Time::GetInstance().GetDeltaTime();
		if (m_InflateTime <= -0.3f)
			return int(Pooka::PookaState::WANDER);
	}

	if (m_InflateTime < 0.8f)
	{
		m_pAnim->SetCurrentAnimation(1, 0.5f, 0);
		pObj->GetTransform()->SetScale(1.1f, 1.1f);
	}
	else if (m_InflateTime < 1.6f)
	{
		m_pAnim->SetCurrentAnimation(2, 0.5f, 0);
		pObj->GetTransform()->SetScale(1.5f, 1.5f);
	}
	else
	{
		m_pAnim->SetCurrentAnimation(3, 0.5f, 0);
		pObj->GetTransform()->SetScale(1.9f, 1.9f);
	}

	if (m_InflateTime >= 2.4f)
	{
		m_pObserver->OnNotify(pObj, dae::Event::POOKA_INFLATED);
		pObj->GetScene()->RemoveChild(pObj);
		return 0;
	}
	return int(Pooka::PookaState::INFLATE);
}

void PookaInflate::Reset()
{
	m_WasPumped = false;
	m_InflateTime = 0;
}
