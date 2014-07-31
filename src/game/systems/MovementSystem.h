#pragma once

#include "System.h"

namespace core
{
	class Entity;
	class MovementSystem : public ecs::System
	{
	public:
		MovementSystem();

	public:
		virtual void Process(Uint32 deltaTime) override;
		virtual bool ValidateEntity(const ecs::Entity* entity) const override;
	};

}