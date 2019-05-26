#include "pch.h"
#include "FPSTestScene.h"
#include "GameObject.h"
#include "Font.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "GridRenderComponent.h"
#include "ImageComponent.h"
#include "Time.h"
#include "Player.h"
#include "GridHelper.h"
#include "CollisionBoxComponent.h"
#include "Stone.h"
#include "Pooka.h"
#include "Fygar.h"
#include "ScoreObserver.h"

FPSTestScene::FPSTestScene()
	:m_pScoreObserver{}
{
	Initialize();
}


FPSTestScene::~FPSTestScene()
{
	delete m_pScoreObserver;
}

void FPSTestScene::Update()
{
	
	
}

void FPSTestScene::Draw()
{
	
}

void FPSTestScene::Initialize()
{
	auto* grid = new dae::GameObject{};
	AddChild(grid);
	m_pGridComp = new dae::GridRenderComponent{ "tileset.png", int(dae::GridHelper::GetRows()), int(dae::GridHelper::GetColumns()) };
	grid->AddComponent(m_pGridComp);

	auto* text = new dae::GameObject{};
	AddChild(text);
	auto* score = new dae::TextComponent{ "0","../Data/Lingua.otf",20 };
	text->AddComponent(score);
	text->GetTransform()->Translate(600.0f, 400.0f);

	auto* player = Player::CreatePlayer(m_pGridComp,this);
	
	m_pScoreObserver = new ScoreObserver{ score };

	auto* pooka = Pooka::CreatePooka(m_pGridComp,this,m_pScoreObserver,player,nullptr);
	pooka->GetTransform()->SetPosition({402.5f,235.0f,0.4f});
	//
	auto * fygar = Fygar::CreateFygar(m_pGridComp, this,m_pScoreObserver, player);
	fygar->GetTransform()->SetPosition({ 402.5f,260.0f,0.4f });
	float tileSize{ dae::GridHelper::GetTileSize() };
	for (int i{}; i < 27; ++i)
	{
		for (int j{}; j < 70; ++j)
		{
			m_pGridComp->SetTileId(dae::GridHelper::GetTile(i*tileSize, j*tileSize), 3);
		}
	}
	
	for (int i{128-27}; i < 128; ++i)
	{
		for (int j{}; j < 70; ++j)
		{
			m_pGridComp->SetTileId(dae::GridHelper::GetTile(i*tileSize, j*tileSize), 3);
		}
	}
	
	for (int i{ 27 }; i < 101; ++i)
	{
		for (int j{}; j < 70; ++j)
		{
			m_pGridComp->SetTileId(dae::GridHelper::GetTile(i*tileSize, j*tileSize), j/25);
		}
	}
	
	for (int i{ 78 }; i < 83; ++i)
	{
		for (int j{ 30 }; j < 65; ++j)
		{
			m_pGridComp->SetTileId(dae::GridHelper::GetTile(i*tileSize, j*tileSize), 999);
		}
	}
	
	auto* stone = Stone::CreateStone(m_pGridComp, this);
	

	dae::InputManager::GetInstance().Assignbutton("Pump", dae::Button::ButtonA);
	dae::InputManager::GetInstance().Assignbutton("BDown", dae::Button::ButtonB);
	dae::InputManager::GetInstance().Assignbutton("XUp", dae::Button::ButtonX);
	dae::InputManager::GetInstance().Assignbutton("Down", dae::Button::DPadDown);
	dae::InputManager::GetInstance().Assignbutton("Up", dae::Button::DPadUp);
	dae::InputManager::GetInstance().Assignbutton("Left", dae::Button::DPadLeft);
	dae::InputManager::GetInstance().Assignbutton("Right", dae::Button::DPadRight);
	//programID = dae::ResourceManager::GetInstance().LoadShaders("vertexShader.glsl", "pixelShader.glsl");
}

