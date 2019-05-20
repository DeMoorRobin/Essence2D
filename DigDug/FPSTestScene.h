#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "GridRenderComponent.h"

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
	GLuint vertexBuffer;
	GLuint programID;
	GLuint indexBuffer;

	dae::GameObject* m_pPlayer;
	dae::GridRenderComponent* m_pGridComp;
	void RemoveTiles();
	bool CanMoveY();
	bool CanMoveX();
	GLuint GetTileX(float x);
	GLuint GetTileY(float y);
	GLuint GetTile(float x, float y);
};


