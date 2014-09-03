#include "pch.h"
#include "MovementSystem.h"
#include "Position.h"
#include "InputController.h"

namespace ecs
{
	MovementSystem::MovementSystem(core::ecs::World& world)
		: System(world)
	{
		m_type = core::ecs::SystemType::Logic;
	}

	void MovementSystem::Process(Uint32 deltaTime)
	{
		const float speed = 0.05f;
		for (auto e : m_world.GetEntitiesWith<ecs::Position, ecs::Direction>())
		{
			auto &p = *m_world.GetComponent<ecs::Position>(e);
			auto &d = *m_world.GetComponent<ecs::Direction>(e);

			p.x += d.x * deltaTime * speed;
			p.y += d.y * deltaTime * speed;
		}
	}	
}