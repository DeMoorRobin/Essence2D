#pragma once

class GameObject;

namespace dae
{

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;

	protected:
		GameObject* m_pGameObject;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
	};
}


