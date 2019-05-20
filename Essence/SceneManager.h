#pragma once
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;

		void BaseUpdate();
		void BaseDraw();

		void AddScene(Scene* pScene);
		Scene* GetActiveScene();

	private:
		Scene* m_pActiveScene;
		std::vector<Scene*> m_pScenes;

	};
}

