#pragma once

#include "System.h"

namespace core
{
	class MovementSystem : public ecs::System
	{
	public:
		MovementSystem();

	public:
		virtual void Process(Uint32 deltaTime) override;
	};

}