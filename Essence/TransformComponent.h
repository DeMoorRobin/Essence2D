#pragma once
#include "BaseComponent.h"


namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		virtual ~TransformComponent() = default;

		//TransformComponent is allowed to be copied, moved, ...

		//TransformComponent(const TransformComponent& other) = delete;
		//TransformComponent(TransformComponent&& other) noexcept = delete;
		//TransformComponent& operator=(const TransformComponent& other) = delete;
		//TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		const glm::vec3& GetPosition() const { return m_Position; };
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& pos);
		void Translate(float x, float y, float z = 0);
		void Translate(const glm::vec3& dMovement);
		void Translate(const glm::vec2& dMovement);
		void SetScale(const glm::vec2& scale);
		void SetScale(float x, float y);


		const glm::vec2& GetScale() { return m_Scale; };


		void SetPivotOffset(float x, float y);
		void SetPivotOffset(const glm::vec2& offset);
	protected:
		void Initialize() override;
		void Update() override;


	private:
		glm::vec3 m_Position;
		glm::vec2 m_Scale;
		glm::vec2 m_PivotOffset;
	};
}


