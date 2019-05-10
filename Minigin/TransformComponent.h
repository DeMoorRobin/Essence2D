#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

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
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);

		bool HasChanged() const{ return m_HasChanged; };

	protected:
		void Initialize() override;
		void Update() override;


	private:
		glm::vec3 m_Position;
		bool m_HasChanged;
	};
}


