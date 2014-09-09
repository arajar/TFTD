#include "pch.h"
#include "RenderSystem.h"
#include "Renderable.h"
#include "Transform.h"

namespace ecs
{
	RenderSystem::RenderSystem(core::ecs::World& world)
		: System(world)
	{
		m_type = core::ecs::SystemType::Render;
	}

	void RenderSystem::Process(sf::RenderTarget& target)
	{
		for (auto e : m_world.GetEntitiesWith<ecs::Transform, ecs::Renderable>())
		{
			auto& p = *m_world.GetComponent<ecs::Transform>(e);
			auto& r = *m_world.GetComponent<ecs::Renderable>(e);

			r.SetPosition(p.GetPosition());
			r.Render(target);
		}
	}

	RenderDebugSystem::RenderDebugSystem(core::ecs::World& world)
		: System(world)
	{
		m_priority = 1000;
		m_type = core::ecs::SystemType::Render;
	}

	void RenderDebugSystem::Process(sf::RenderTarget& target)
	{
		for (auto e : m_world.GetEntitiesWith<ecs::Renderable>())
		{
			auto& r = *m_world.GetComponent<ecs::Renderable>(e);

			r.RenderDebug(target);
		}
	}
}