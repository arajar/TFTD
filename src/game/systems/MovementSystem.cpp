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

	void MovementSystem::Process(sf::Time deltaTime)
	{
		const float speed = 1.f;
		for (auto e : m_world.GetEntitiesWith<ecs::Position, ecs::Direction>())
		{
			auto &p = *m_world.GetComponent<ecs::Position>(e);
			auto &d = *m_world.GetComponent<ecs::Direction>(e);

			p.x += d.x * deltaTime.asMilliseconds() * speed;
			p.y += d.y * deltaTime.asMilliseconds() * speed;
		}
	}	
}