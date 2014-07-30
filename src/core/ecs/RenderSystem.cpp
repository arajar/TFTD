#include "pch.h"
#include "RenderSystem.h"

namespace core
{
	RenderSystem::RenderSystem()
	{
		m_type = ecs::SystemType::Render;
	}

	void RenderSystem::Process(Uint32 deltaTime)
	{

	}
}