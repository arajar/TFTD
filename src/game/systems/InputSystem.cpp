#include "pch.h"
#include "InputSystem.h"
#include "Position.h"
#include "Direction.h"

namespace ecs
{
	InputSystem::InputSystem(core::ecs::World& world)
		: System(world)
	{
		m_type = core::ecs::SystemType::Logic;
	}

	void InputSystem::Process(Uint32 deltaTime)
	{
		for (auto e : m_world.GetEntitiesWith<ecs::Position, ecs::Direction>())
		{
			auto &p = *m_world.GetComponent<ecs::Position>(e);
			auto &d = *m_world.GetComponent<ecs::Direction>(e);

			p.x += d.x * deltaTime;
			p.y += d.y * deltaTime;
		}
	}
}