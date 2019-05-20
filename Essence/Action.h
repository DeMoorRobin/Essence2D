#pragma once
namespace dae
{
	class GameObject;
	class Action
	{
	public:
		virtual ~Action() = 0;
		virtual void Execute() = 0;
	};

}

