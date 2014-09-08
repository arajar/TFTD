#pragma once

#include "ecs/System.h"

namespace ecs
{
	class AnimationSystem : public core::ecs::System
	{
	public:
		AnimationSystem(core::ecs::World& world);

	public:
		virtual void Process(sf::Time deltaTime) override;
	};

}