#pragma once
#include "Observer.h"
namespace dae
{
	class GameObject;
	class TextComponent;
}
class ScoreObserver final : public dae::Observer
{
public:
	ScoreObserver(dae::TextComponent* m_pScoreText);
	~ScoreObserver() = default;

	void OnNotify(dae::GameObject* pObj,  dae::Event event) override;
private:
	int m_TotalScore;
	float m_Height1, m_Height2;
	dae::TextComponent* m_pTextComponent;
};

