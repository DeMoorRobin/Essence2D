#include "MiniginPCH.h"
#include "FPSTestScene.h"
#include "GameObject.h"
#include "Font.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"


FPSTestScene::FPSTestScene()
{
	Initialize();
}


FPSTestScene::~FPSTestScene()
{
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
	dae::GameObject* fpsObject = new dae::GameObject();
	AddChild(fpsObject);
	//
	dae::TextComponent* textComp = new dae::TextComponent{"mho","../Data/Lingua.otf" ,10};
	fpsObject->AddComponent(textComp);
	//TransformComponent* plop = new TransformComponent{};
	//fpsObject->AddComponent(plop);

	dae::InputManager::GetInstance().Assignbutton("A", dae::ControllerButton::ButtonA);
	dae::InputManager::GetInstance().Assignbutton("BDown", dae::ControllerButton::ButtonB);
	dae::InputManager::GetInstance().Assignbutton("XUp", dae::ControllerButton::ButtonX);

}