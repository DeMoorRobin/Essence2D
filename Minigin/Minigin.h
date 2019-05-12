#pragma once

struct SDL_Window;

namespace dae
{
	class SceneManager;
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
		SDL_GLContext m_pContext;
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

	private:
		SceneManager* m_pSceneManager;
	};
}