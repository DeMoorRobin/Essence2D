#pragma once
namespace dae
{
	class GameObject;
	class State
	{
	public:
		virtual ~State() {};
		virtual int Update(GameObject* pObj) = 0;
		virtual void Reset() = 0;
	};
}
