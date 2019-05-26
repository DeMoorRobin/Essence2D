#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"


dae::SceneManager* dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	
	

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	m_pContext = SDL_GL_CreateContext(window);
	if (m_pContext == nullptr)
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	
	//SDL_GL_MakeCurrent(window, m_pContext);
	glewExperimental = GL_TRUE;

	auto test = glewInit();
	if (test == GLEW_OK)std::cout << "Glew ok\n";
	

	SDL_GL_SetSwapInterval(0);

	m_pSceneManager = new dae::SceneManager{};
	auto er = glGetError();
	if (GL_NO_ERROR != er)
	{
		std::cout << gluErrorString(er) << std::endl;
	}
	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, 640, 480);

	GLuint vertexArrayID{};
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glDepthFunc(GL_NEVER);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ResourceManager::GetInstance().Init("../Data/");
	return m_pSceneManager;
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//I let the user create Objects that inherit from Scene.
	//This allows the user to add member functions and variables
	//Scenes are added to the SceneManager which then has ownership and thus manages the deletion as well
	//Scene* scene = new FPSTestScene{};
	//m_pSceneManager->AddScene(scene);

	//auto go = std::make_shared<GameObject>();
	//go->SetTexture("background.jpg");
	//scene.Add(go);
	//
	//go = std::make_shared<GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

void dae::Minigin::Cleanup()
{
	SDL_GL_DeleteContext(m_pContext);
	SDL_DestroyWindow(window);
	delete m_pSceneManager;
	window = nullptr;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void dae::Minigin::Run()
{
	// tell the resource manager where he can find the game data
	

	//LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		//auto& renderer = Renderer::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			//std::cout << "Frame" << std::endl;
			doContinue = input.ProcessInput();
			Time::GetInstance().EnterNextFrame();

			m_pSceneManager->BaseUpdate();
			m_pSceneManager->BaseDraw();
			SDL_GL_SwapWindow(window);
			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
