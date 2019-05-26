#include "pch.h"
#include "Pump.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "RenderComponent.h"
#include "PlayerBehavior.h"
#include "CollisionBoxComponent.h"
#include "Scene.h"
#include "StateMachineComponent.h"
#include "PlayerMoveBehavior.h"

dae::GameObject * Pump::CreatePump(dae::Scene * pScene, PlayerPumpState::Direction dir)
{
	auto* pump = new dae::GameObject{};
	pScene->AddChild(pump);
	switch (dir)
	{
	case PlayerPumpState::Direction::LEFT:
	{
		auto* sprite = new dae::ImageComponent{ "SpriteSheet.png", 50.0f, 20.0f,{4.0f*32.0f / 448.0f, 0 ,64.0f / 448.0f,16.0f / 224.0f} };
		pump->AddComponent(sprite);
		break;
	}
		
	case PlayerPumpState::Direction::RIGHT:
	{
		auto* sprite = new dae::ImageComponent{ "SpriteSheet.png", 50.0f, 20.0f,{4.0f*32.0f / 448.0f, 16.0f / 224.0f ,64.0f / 448.0f,16.0f / 224.0f} };
		pump->AddComponent(sprite);
		break;
	}
	case PlayerPumpState::Direction::UP:
	{
		auto* sprite = new dae::ImageComponent{ "SpriteSheet.png", 20.0f, 50.0f,{(448.0f - 32.0f) / 448.0f, 64.0f / 224.0f ,16.0f / 448.0f,64.0f / 224.0f} };
		pump->AddComponent(sprite);
		break;
	}
	case PlayerPumpState::Direction::DOWN:
	{
		auto* sprite = new dae::ImageComponent{ "SpriteSheet.png", 20.0f, 50.0f,{(448.0f - 16.0f) / 448.0f, 64.0f / 224.0f ,16.0f / 448.0f,64.0f / 224.0f} };
		pump->AddComponent(sprite);
		break;
	}
	}
	

	return pump;
}


