#include "pch.h"
#include "PookaInflate.h"
#include "Time.h"
#include "GameObject.h"
#include "Scene.h"
#include "Pooka.h"
PookaInflate::PookaInflate()
	:m_InflateTime{}
	,m_WasPumped{}
{
}

int PookaInflate::Update(dae::GameObject * pObj)
{
	if (m_WasPumped)
	{
		m_InflateTime += dae::Time::GetInstance().GetDeltaTime();
		if (m_InflateTime >= 2.0f)
		{
			pObj->GetScene()->RemoveChild(pObj);
			return 0;
		}
		m_WasPumped = false;
	}
	else
	{
		m_InflateTime -= dae::Time::GetInstance().GetDeltaTime();
		if (m_InflateTime <= -0.3f)
			return int(Pooka::PookaState::WANDER);
	}
	return int(Pooka::PookaState::INFLATE);
}

void PookaInflate::Reset()
{
	m_WasPumped = false;
	m_InflateTime = 0;
}
