#include "pch.h"
#include "AnimationSystem.h"
#include "Skeleton2D.h"

namespace ecs
{
	AnimationSystem::AnimationSystem(core::ecs::World& world)
		: System(world)
	{
		//m_priority = 1;
		m_type = core::ecs::SystemType::Logic;
	}

	void AnimationSystem::Process(sf::Time deltaTime)
	{
		for (auto e : m_world.GetEntitiesWith<ecs::Skeleton2D>())
		{
			auto& s = *m_world.GetComponent<ecs::Skeleton2D>(e);
			s.Update(deltaTime);
		}
	}
}