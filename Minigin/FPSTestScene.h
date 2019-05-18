#pragma once
#include "Scene.h"
#include "GameObject.h"
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
};


