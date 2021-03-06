#pragma once

namespace dae
{
	class BaseComponent;
	class TransformComponent;
	class RenderComponent;
	class Scene;

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

		void AddComponent(BaseComponent* pComp);
		//void RemoveComponent(BaseComponent* pComp);

		RenderComponent* GetRenderComponent() const { return m_pRenderComponent; };
		TransformComponent* GetTransform()const { return m_pTransform; };

		void RelinkComponents();

		void SetScene(Scene* pScene) { m_pScene = pScene; };
		Scene* GetScene() { return m_pScene; };

		template<typename T>
		T GetComponent()
		{
			for (auto* pComp : m_pComponents)
			{
				if (dynamic_cast<T>(pComp))
				{
					return (T)pComp;
				}
			}
			return nullptr;
		}

	protected:
		//virtual void Update() = 0;
		//virtual void Draw() = 0;
		Scene* m_pScene;

	private:

		std::vector<BaseComponent*> m_pComponents;
		TransformComponent* m_pTransform;
		RenderComponent* m_pRenderComponent;
		
	};
}


