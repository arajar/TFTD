#include "pch.h"
#include "RenderSystem.h"
#include "Sprite.h"
#include "Position.h"
//#include "Direction.h"

namespace ecs
{
	RenderSystem::RenderSystem(core::ecs::World& world)
		: System(world)
	{
		m_type = core::ecs::SystemType::Render;
	}

	void RenderSystem::Process()
	{
		for (auto e : m_world.GetEntitiesWith<ecs::Position, ecs::Sprite>())
		{
			auto &p = *m_world.GetComponent<ecs::Position>(e);
			auto &s = *m_world.GetComponent<ecs::Sprite>(e);

			s.SetPosition(glm::ivec2(p.x, p.y));
			s.Render();
		}
	}
}