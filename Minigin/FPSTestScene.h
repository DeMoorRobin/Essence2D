#pragma once
#include "Scene.h"

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
	};


