#pragma once

namespace dae
{
	class BaseComponent;
	class TransformComponent;
	class RenderComponent;

	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;


		//void Initialize();
		void BaseUpdate();
		void BaseDraw();


		//void AddChild(GameObject* pObj);
		//void RemoveChild(GameObject* pObj);

		void AddComponent(BaseComponent* pComp);
		//void RemoveComponent(BaseComponent* pComp);

	protected:
		//virtual void Update() = 0;
		//virtual void Draw() = 0;

	private:

		std::vector<GameObject*> m_Children;
		std::vector<BaseComponent*> m_pComponents;
		TransformComponent* m_pTransform;
		RenderComponent* m_pRenderComponent;
	};
}


