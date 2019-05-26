#pragma once
#include <unordered_map>

namespace dae
{
	class GameObject;
	class RenderComponent;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void BaseUpdate();
		void BaseDraw();

		void AddChild(GameObject* pObj);
		void RemoveChild(GameObject* pObj);

		RenderComponent* RequestRenderComponent(GameObject* pObj);

	protected:

		virtual void Update() = 0;
		virtual void Draw() = 0;

	private:
		std::vector<GameObject*> m_pChildren;
		std::vector<RenderComponent> m_RenderComponents;
		std::unordered_map<GameObject*, RenderComponent*> m_ObjToRenderMap;


	};
}


