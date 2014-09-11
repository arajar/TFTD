#pragma once

#include "ecs/System.h"

class Entity;

namespace ecs
{
	class MovementSystem : public core::ecs::System
	{
		NAME(MovementSystem)

	public:
		explicit MovementSystem(core::ecs::World& world);

	public:
		virtual void Process(sf::Time deltaTime) override;
	};
}