#pragma once

namespace dae
{
	class GameObject;


	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent(bool requiresRenderComponent = false);
		virtual ~BaseComponent() = default;

		bool RequiresRenderComponent() { return m_RequiresRenderComponent; };
		void SetGameObject(GameObject* pObject) { m_pGameObject = pObject; };
	protected:
		GameObject* m_pGameObject;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
	private:
		bool m_RequiresRenderComponent;
	};
}


