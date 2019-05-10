#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent()
	:m_HasChanged(true)
	,m_Position{}
{
}

void dae::TransformComponent::Initialize()
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}
void dae::TransformComponent::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}