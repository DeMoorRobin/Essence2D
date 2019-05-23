#pragma once
namespace dae
{
	class CollisionBoxComponent;
	class CollisionCommand
	{
	public:
		virtual ~CollisionCommand() {};
		virtual void Update(CollisionBoxComponent* pOwner) = 0;
		virtual void Execute(CollisionBoxComponent* pOther,CollisionBoxComponent * pOwner) = 0;
	};
}
