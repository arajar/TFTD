#include "pch.h"
#include "MovementSystem.h"
#include "Position.h"
#include "Transform.h"

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
		for (auto e : m_world.GetEntitiesWith<ecs::Transform, ecs::Direction>())
		{
			auto& t = *m_world.GetComponent<ecs::Transform>(e);
			auto& d = *m_world.GetComponent<ecs::Direction>(e);

			auto dt = static_cast<float>(deltaTime.asMilliseconds());

			t.Translate(d.dir * dt * speed);
		}
	}	
}