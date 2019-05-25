#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:BaseComponent{}
	,m_Position{}
	,m_Scale{1.0f,1.0f}
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

void dae::TransformComponent::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void dae::TransformComponent::Translate(const glm::vec3& dMovement)
{
	m_Position += dMovement;
}

void dae::TransformComponent::Translate(const glm::vec2& dMovement)
{
	Translate(dMovement.x, dMovement.y);
}

void dae::TransformComponent::SetPivotOffset(float x, float y)
{
	m_PivotOffset.x = x;
	m_PivotOffset.y = y;
}

void dae::TransformComponent::SetPivotOffset(const glm::vec2& offset)
{
	m_PivotOffset = offset;
}

void dae::TransformComponent::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
}

void dae::TransformComponent::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}