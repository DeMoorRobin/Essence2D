#include "pch.h"
#include "Stone.h"
#include "GameObject.h"
#include "GridRenderComponent.h"
#include "ImageComponent.h"
#include "CollisionBoxComponent.h"
#include "StoneBehavior.h"
#include "Scene.h"
#include "TransformComponent.h"

dae::GameObject * Stone::CreateStone(dae::GridRenderComponent *pGrid, dae::Scene* pScene)
{
	auto* stone{ new dae::GameObject{} };
	stone->GetTransform()->SetPosition({ 263.0f,260.0f, 0.4f });
	pScene->AddChild(stone);
	stone->AddComponent(new dae::ImageComponent{ "SpriteSheet.png",25.0f,25.0f,{32.0f / 448.0f,0,32.0f / 448.0f,32.0f/224.0f} });
	auto* pCollisionPlayerCheck = new dae::CollisionBoxComponent{ 3,11,false,false };
	stone->AddComponent(pCollisionPlayerCheck);
	stone->AddComponent(new dae::CollisionBoxComponent{ 5,5,true, false });
	stone->AddComponent(new StoneBehavior{ pGrid, pCollisionPlayerCheck });
	return stone ;
}

