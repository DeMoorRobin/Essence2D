// DigDug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <vld.h>
#include "SDL.h"
#include "pch.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "FPSTestScene.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) 
{
#pragma warning( pop )

	dae::Minigin engine;
	auto* sceneManager = engine.Initialize();
	sceneManager->AddScene(new FPSTestScene{});
	engine.Run();
	return 0;
}