#include "pch.h"
#include "Pooka.h"
#include "GameObject.h"
#include "GridRenderComponent.h"
#include "ImageComponent.h"
#include "CollisionBoxComponent.h"
#include "RespectBoundaries.h"
#include "BlockMovement.h"
#include "StateMachineComponent.h"
#include "PookaWander.h"
#include "PookaChase.h"
#include "State.h"
#include "Scene.h"
#include "Inflatable.h"
#include "PookaInflate.h"
#include "AnimationRenderComponent.h"
#include "SquishAble.h"
#include "SquishState.h"

dae::GameObject * Pooka::CreatePooka(dae::GridRenderComponent * pGrid,dae::Scene* pScene, dae::Observer* pScoreObserver, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2)
{
	auto* pooka{ new dae::GameObject{} };
	pScene->AddChild(pooka);
	

	auto* pAnim{ new dae::AnimationRenderComponent{"SpriteSheet.png",25.0f,25.0f} };
	pooka->AddComponent(pAnim);
	std::vector<dae::Frame>* run{ new std::vector<dae::Frame>{} };
	run->push_back(dae::Frame{ 0,32.0f / 224.0f,32.0f / 448.0f,32.0f / 224.0f });
	run->push_back(dae::Frame{ 32.0f / 448.0f,32.0f / 224.0f,32.0f / 448.0f,32.0f / 224.0f});

	std::vector <dae::Frame>* inf1{ new std::vector<dae::Frame>{} };
	inf1->push_back(dae::Frame{194.0f / 448.0f,0,34.0f / 448.0f,34.0f / 224.0f });

	std::vector <dae::Frame>* inf2{ new std::vector<dae::Frame>{} };
	inf2->push_back(dae::Frame{ 228.0f / 448.0f,0,44.0f / 448.0f,44.0f / 224.0f });

	std::vector <dae::Frame>* inf3{ new std::vector<dae::Frame>{} };
	inf3->push_back(dae::Frame{ 228.0f / 448.0f,0,44.0f / 448.0f,44.0f / 224.0f });

	pAnim->AddAnimation(run, 0);
	pAnim->AddAnimation(inf1, 1);
	pAnim->AddAnimation(inf2, 2);
	pAnim->AddAnimation(inf3, 3);
	pAnim->SetCurrentAnimation(0, 0.3f, 0, true);
	
	auto* collision{ new dae::CollisionBoxComponent{5,5,false,false} };
	pooka->AddComponent(collision);
	collision->AddCommand(new RespectBoundaries{ 27,101,0,77 });
	collision->AddCommand(new dae::BlockMovement{});

	auto* stateMachine{ new dae::StateMachineComponent{0} };
	std::vector<dae::State*> pStates{};
	pStates.push_back(new PookaWander(pGrid, 25.0f,60.0f,pPlayer1,pPlayer2,pAnim));
	pStates.push_back(new PookaChase{ pGrid, 25.0f, 70.0f,pPlayer1,pPlayer2,pAnim });
	auto inf = new PookaInflate{pAnim,pScoreObserver};
	pStates.push_back(inf);
	pStates.push_back(new SquishState{ pScene,pAnim,pScoreObserver });
	stateMachine->SetStateVector(pStates);
	pooka->AddComponent(stateMachine);
	pooka->AddComponent(new Inflatable{stateMachine,inf,nullptr, int(Pooka::PookaState::INFLATE)});
	pooka->AddComponent(new SquishAble{ stateMachine,int(Pooka::PookaState::SQUISH) });

	return pooka;
}
