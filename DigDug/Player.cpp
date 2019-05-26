#include "pch.h"
#include "Player.h"
#include "ImageComponent.h"
#include "RenderComponent.h"
#include "PlayerBehavior.h"
#include "GridRenderComponent.h"
#include "CollisionBoxComponent.h"
#include "AnimationRenderComponent.h"
#include "RespectBoundaries.h"
#include "BlockMovement.h"
#include "Scene.h"
#include "StateMachineComponent.h"
#include "PlayerMoveBehavior.h"
#include "PlayerPumpState.h"

dae::GameObject * Player::CreatePlayer(dae::GridRenderComponent* pGrid, dae::Scene* pScene)
{
	auto* player = new dae::GameObject{};
	pScene->AddChild(player);
	auto* anim = new dae::AnimationRenderComponent{ "SpriteSheet.png",25.0f,25.0f };
	player->AddComponent(anim);

	std::vector<dae::Frame>* runRight{ new std::vector<dae::Frame>{} };
	runRight->push_back(dae::Frame{ 0, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	runRight->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* runLeft{ new std::vector<dae::Frame>{} };
	runLeft->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	runLeft->push_back(dae::Frame{ 64.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* runUp{ new std::vector<dae::Frame>{} };
	runUp->push_back(dae::Frame{ 0.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	runUp->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* runDown{ new std::vector<dae::Frame>{} };
	runDown->push_back(dae::Frame{ 0.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	runDown->push_back(dae::Frame{ 32.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digRight{ new std::vector<dae::Frame> {} };
	digRight->push_back(dae::Frame{ 64.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digRight->push_back(dae::Frame{ 96.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digRight->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digRight->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 32.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digLeft{ new std::vector<dae::Frame> {} };
	digLeft->push_back(dae::Frame{ 96.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	digLeft->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	digLeft->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });
	digLeft->push_back(dae::Frame{ 192.0f / 448.0f, (224.0f - 32.0f) / 224.0f,-32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digUp{ new std::vector<dae::Frame> {} };
	digUp->push_back(dae::Frame{ 64.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digUp->push_back(dae::Frame{ 96.0f / 448.0f,  (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digUp->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digUp->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 96.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	std::vector<dae::Frame>* digDown{ new std::vector<dae::Frame> {} };
	digDown->push_back(dae::Frame{ 64.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digDown->push_back(dae::Frame{ 96.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digDown->push_back(dae::Frame{ 128.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	digDown->push_back(dae::Frame{ 160.0f / 448.0f, (224.0f - 64.0f) / 224.0f,32.0f / 448.0f,32.0f / 224.0f });

	anim->AddAnimation(runRight, int(PlayerMoveBehavior::Animation::RUNRIGHT));
	anim->AddAnimation(runLeft, int(PlayerMoveBehavior::Animation::RUNLEFT));
	anim->AddAnimation(runUp, int(PlayerMoveBehavior::Animation::RUNUP));
	anim->AddAnimation(runDown, int(PlayerMoveBehavior::Animation::RUNDOWN));
	anim->AddAnimation(digRight, int(PlayerMoveBehavior::Animation::DIGRIGHT));
	anim->AddAnimation(digLeft, int(PlayerMoveBehavior::Animation::DIGLEFT));
	anim->AddAnimation(digUp, int(PlayerMoveBehavior::Animation::DIGUP));
	anim->AddAnimation(digDown, int(PlayerMoveBehavior::Animation::DIGDOWN));
	anim->SetCurrentAnimation(int(PlayerMoveBehavior::Animation::RUNRIGHT), 0.3f, 0, true);

	 

	auto* collision = new dae::CollisionBoxComponent{5,5,false,false};
	player->AddComponent(collision);

	auto* block = new dae::BlockMovement{};
	collision->AddCommand(block);
	collision->AddCommand(new RespectBoundaries{ 27,101,0,77 });

	auto* stateMachine = new dae::StateMachineComponent{ 0 };
	std::vector<dae::State*> states{};
	states.push_back(new PlayerMoveBehavior{ pGrid,anim });
	states.push_back(new PlayerPumpState{pScene,anim});
	player->AddComponent(stateMachine);
	stateMachine->SetStateVector(states);

	player->GetTransform()->SetPosition( 368.0f,260.0f, 0.3f);

	return player;
}

