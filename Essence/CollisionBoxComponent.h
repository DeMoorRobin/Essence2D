#pragma once
#include "BaseComponent.h"
namespace dae
{
	class CollisionCommand;
	class CollisionBoxComponent final : public BaseComponent
	{
	public:
		CollisionBoxComponent(int sizeX, int sizeY, bool isStatic, bool isTrigger);
		~CollisionBoxComponent();
		const SDL_Rect& GetCurrentRect() { return m_CurrentRect; };
		void TriggerCollision(CollisionBoxComponent* pOther);

		void AddCommand(CollisionCommand* pCommand) { m_pCommands.push_back(pCommand); };
		bool IsStatic() { return m_IsStatic; };
		void PrepareCollision();
		void EnableStatic(bool enable) {m_IsStatic = enable;};

		void ClearCommands();

	protected:
		void Initialize() override;
		void Update() override;
	private:
		bool m_IsStatic;
		bool m_IsTrigger;
		std::vector<CollisionCommand*> m_pCommands;

		//tiles
		SDL_Rect m_CurrentRect;
		int m_SizeX, m_SizeY;

	};
}
