#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(bool requiresRenderComponent)
	:m_RequiresRenderComponent{ requiresRenderComponent }
{
}



