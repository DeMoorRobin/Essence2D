#include "pch.h"
#include "Player.h"
#include "ImageComponent.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "PlayerBehavior.h"
#include "GridRenderComponent.h"
#include "CollisionBoxComponent.h"
#include "AnimationRenderComponent.h"
#include "RespectBoundaries.h"
#include "BlockMovement.h"


dae::GameObject * Player::CreatePlayer(dae::GridRenderComponent* pGrid)
{
	auto* player = new dae::GameObject{};
	auto* anim = new dae::AnimationRenderComponent{ "SpriteSheet.png",25.0f,25.0f };
	dae::RenderComponent* renderComp = dae::Renderer::GetInstance().RequestRenderComponent();
	player->AddRenderComponent(renderComp);
	player->AddComponent(anim);

	player->AddComponent(new PlayerBehavior{pGrid,anim});

	auto* collision = new dae::CollisionBoxComponent{5,5,false,false};
	player->AddComponent(collision);

	collision->AddCommand(new dae::BlockMovement{});
	collision->AddCommand(new RespectBoundaries{ 27,101,0,77 });

	player->GetTransform()->Translate(320.0f, 240.0f, 0.3f);

	return player;
}

