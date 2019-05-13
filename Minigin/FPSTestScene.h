#pragma once
#include "Scene.h"
#include "GameObject.h"

	class FPSTestScene final : public dae::Scene
	{
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


