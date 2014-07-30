#include "pch.h"
#include "MovementSystem.h"

namespace core
{
	MovementSystem::MovementSystem()
	{
		m_type = ecs::SystemType::Logic;
		AddRequirement<Position>();
		AddRequirement<Direction>();
	}

	void MovementSystem::Process(Uint32 deltaTime)
	{
		for (const auto& e : m_entities)
		{
			auto p = e->GetComponent<Position>();
			auto d = e->GetComponent<Direction>();

			p->x += d->x * deltaTime;
			p->y += d->y * deltaTime;
		}
	}
}