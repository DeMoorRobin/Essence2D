#include "pch.h"
#include "Player.h"
#include "ImageComponent.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "PlayerBehavior.h"
#include "GridRenderComponent.h"

#include "AnimationRenderComponent.h"


dae::GameObject * Player::CreatePlayer(dae::GridRenderComponent* pGrid)
{
	auto* player = new dae::GameObject{};
	auto* anim = new dae::AnimationRenderComponent{ "SpriteSheet.png",25.0f,25.0f };
	dae::RenderComponent* renderComp = dae::Renderer::GetInstance().RequestRenderComponent();
	player->AddRenderComponent(renderComp);
	player->AddComponent(anim);

	player->AddComponent(new PlayerBehavior{pGrid,anim});



	player->GetTransform()->Translate(320.0f, 240.0f, 0.3f);

	return player;
}

