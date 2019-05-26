#include "pch.h"
#include "ScoreObserver.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

ScoreObserver::ScoreObserver(dae::TextComponent* pScoreText)
	:m_pTextComponent{pScoreText}
	,m_Height1{100.0f}
	,m_Height2{220.0f}
{
}

void ScoreObserver::OnNotify(dae::GameObject * pObj, dae::Event event)
{
	switch (event)
	{
	case dae::Event::POOKA_INFLATED:
	{
		float height = pObj->GetTransform()->GetPosition().y;
		if (height < m_Height1) m_TotalScore += 500;
		else if (height < m_Height2) m_TotalScore += 400;
		else m_TotalScore += 300;
		break;
	}
	case dae::Event::FYGAR_INFLATE:
	{
		float height = pObj->GetTransform()->GetPosition().y;
		if (height < m_Height1) m_TotalScore += 500;
		else if (height < m_Height2) m_TotalScore += 400;
		else m_TotalScore += 300;
		break;
	}
	case dae::Event::ENEMY_SQUISHED:
	{
		m_TotalScore += 1000;
		break;
	}
	}

	m_pTextComponent->SetText("Score: " + m_TotalScore);
}