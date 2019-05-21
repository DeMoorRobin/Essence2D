#include "pch.h"
#include "FPSTestScene.h"
#include "GameObject.h"
#include "Font.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GridRenderComponent.h"
#include "ImageComponent.h"
#include "Time.h"
#include "Player.h"

FPSTestScene::FPSTestScene()
{
	Initialize();
}


FPSTestScene::~FPSTestScene()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vertexBuffer);

}

void FPSTestScene::Update()
{
	
	
}

void FPSTestScene::Draw()
{
	
}

void FPSTestScene::Initialize()
{

	//m_pPlayer = new dae::GameObject();
	//AddChild(m_pPlayer);
	////std::cout << sizeof(dae::Texture2D) << std::endl;
	////std::cout << sizeof(dae::RenderComponent) << std::endl;
	//////
	//
	//dae::RenderComponent* renderComp = dae::Renderer::GetInstance().RequestRenderComponent();
	//m_pPlayer->AddRenderComponent(renderComp);
	////
	//
	//auto* image = new dae::ImageComponent{ "SpriteSheet.png",25.0f,25.0f ,glm::vec4{0, (224.0f-32.0f)/224.0f,32.0f / 448.0f,32.0f / 224.0f} };
	//m_pPlayer->AddComponent(image);
	//
	//m_pPlayer->GetTransform()->Translate(320.0f, 240.0f, 0.3f);
	


	auto* grid = new dae::GameObject{};
	auto* render = dae::Renderer::GetInstance().RequestRenderComponent();
	grid->AddRenderComponent(render);
	m_pGridComp = new dae::GridRenderComponent{ "tileset.png",70,128 };
	grid->AddComponent(m_pGridComp);
	AddChild(grid);

	auto* player = Player::CreatePlayer(m_pGridComp);
	AddChild(player);
	//renderComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	//fpsObject->GetTransform()->Translate(320.0f, 240.0f);
	//fpsObject->GetTransform()->SetScale(0.5f, 1.0f);
	//dae::TextComponent* textComp = new dae::TextComponent{"WOLOLOLO","../Data/Lingua.otf" ,10};
	//fpsObject->AddComponent(textComp);
	//TransformComponent* plop = new TransformComponent{};
	//fpsObject->AddComponent(plop);

	//auto* player = new dae::GameObject{};
	//auto* sprite = dae::Renderer::GetInstance().RequestRenderComponent();
	//sprite->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("SpriteSheet.png"));
	//sprite->SetSourceRect(SDL_Rect{ 0,0,32,32 });
	//sprite->SetDestRectDefaultSize(32, 32);
	//player->AddRenderComponent(sprite);
	//player->GetTransform()->SetPosition(30.0f, 30.0f, 30.0f);
	//AddChild(player);

	

	dae::InputManager::GetInstance().Assignbutton("A", dae::Button::ButtonA);
	dae::InputManager::GetInstance().Assignbutton("BDown", dae::Button::ButtonB);
	dae::InputManager::GetInstance().Assignbutton("XUp", dae::Button::ButtonX);
	dae::InputManager::GetInstance().Assignbutton("Down", dae::Button::DPadDown);
	dae::InputManager::GetInstance().Assignbutton("Up", dae::Button::DPadUp);
	dae::InputManager::GetInstance().Assignbutton("Left", dae::Button::DPadLeft);
	dae::InputManager::GetInstance().Assignbutton("Right", dae::Button::DPadRight);
	//programID = dae::ResourceManager::GetInstance().LoadShaders("vertexShader.glsl", "pixelShader.glsl");
}

