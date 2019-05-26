#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "GridRenderComponent.h"
#include "ScoreObserver.h"
class ScoreObserver;
class FPSTestScene final : public dae::Scene
{
	struct Vertex
	{
		GLfloat x, y, z;
		GLfloat u, v;
	};

public:
	FPSTestScene();
	~FPSTestScene();

protected:
	void Update() override;
	void Draw() override;

private:
	void Initialize();

	dae::GameObject* m_pPlayer;
	dae::GridRenderComponent* m_pGridComp;
	ScoreObserver* m_pScoreObserver;
};


