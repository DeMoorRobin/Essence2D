#include "MiniginPCH.h"
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
#include "GL/glew.h"
#include "GridRenderComponent.h"

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
	if (dae::InputManager::GetInstance().GetButton("A"))
	{
		std::cout << "A" << std::endl;
	}
	if (dae::InputManager::GetInstance().GetButtonDown("BDown"))
	{
		std::cout << "BDown" << std::endl;
	}
	if (dae::InputManager::GetInstance().GetButtonUp("XUp"))
	{
		std::cout << "XUp" << std::endl;
	}
}

void FPSTestScene::Draw()
{
	
}

void FPSTestScene::Initialize()
{
	//dae::GameObject* fpsObject = new dae::GameObject();
	//AddChild(fpsObject);
	//std::cout << sizeof(dae::Texture2D) << std::endl;
	//std::cout << sizeof(dae::RenderComponent) << std::endl;
	////

	//dae::RenderComponent* renderComp = dae::Renderer::GetInstance().RequestRenderComponent();
	//fpsObject->AddRenderComponent(renderComp);
	//
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



	auto* grid = new dae::GameObject{};
	auto* render = dae::Renderer::GetInstance().RequestRenderComponent();
	grid->AddRenderComponent(render);
	grid->AddComponent(new dae::GridRenderComponent{"tileset.png",35,64});
	render->SetProgram(dae::ResourceManager::GetInstance().LoadShaders("vertexShader.glsl", "pixelShader.glsl"));
	grid->GetTransform()->Translate(0, 0, -1);
	
	AddChild(grid);

	dae::InputManager::GetInstance().Assignbutton("A", dae::ControllerButton::ButtonA);
	dae::InputManager::GetInstance().Assignbutton("BDown", dae::ControllerButton::ButtonB);
	dae::InputManager::GetInstance().Assignbutton("XUp", dae::ControllerButton::ButtonX);
	//programID = dae::ResourceManager::GetInstance().LoadShaders("vertexShader.glsl", "pixelShader.glsl");
}