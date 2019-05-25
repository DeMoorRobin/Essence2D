#include "pch.h"
#include "Pooka.h"
#include "GameObject.h"
#include "GridRenderComponent.h"
#include "Renderer.h"
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

dae::GameObject * Pooka::CreatePooka(dae::GridRenderComponent * pGrid,dae::Scene* pScene, dae::GameObject* pPlayer1, dae::GameObject* pPlayer2)
{
	auto* pooka{ new dae::GameObject{} };
	pScene->AddChild(pooka);
	pooka->AddComponent(new dae::ImageComponent{ "SpriteSheet.png",25.0f,25.0f,{32.0f / 448.0f,32.0f / 224.0f,32.0f / 448.0f,32.0f / 224.0f} });
	auto* collision{ new dae::CollisionBoxComponent{5,5,false,false} };
	pooka->AddComponent(collision);
	collision->AddCommand(new RespectBoundaries{ 27,101,0,77 });
	collision->AddCommand(new dae::BlockMovement{});

	auto* stateMachine{ new dae::StateMachineComponent{0} };
	std::vector<dae::State*> pStates{};
	pStates.push_back(new PookaWander(pGrid, 25.0f,60.0f,pPlayer1,pPlayer2));
	pStates.push_back(new PookaChase{ pGrid, 25.0f, 70.0f,pPlayer1,pPlayer2 });
	auto inf = new PookaInflate{};
	pStates.push_back(inf);
	stateMachine->SetStateVector(pStates);
	pooka->AddComponent(stateMachine);
	pooka->AddComponent(new Inflatable{stateMachine,inf, 2});

	return pooka;
}
