#pragma once
namespace dae
{
	enum class Event
	{
		FYGAR_INFLATE, POOKA_INFLATED, ENEMY_SQUISHED
	};

	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(GameObject* pObj, Event event) = 0;
	};


}
