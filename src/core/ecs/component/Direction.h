#pragma once

#include "Component.h"

namespace core
{
	class Direction : public ecs::Component
	{
		REGISTER_COMPONENT(Direction)

	public:
		float x = 0.f;
		float y = 0.f;
	};
}
