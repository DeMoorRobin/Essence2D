#pragma once


namespace dae
{
	class GameObject;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void BaseUpdate();
		void BaseDraw();

		void AddChild(GameObject* pObj);

	protected:

		virtual void Update() = 0;
		virtual void Draw() = 0;

	private:
		std::vector<GameObject*> m_pChildren;

	};
}


