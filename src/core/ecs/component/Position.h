#pragma once

#include "Component.h"

namespace core
{
	class Position : public ecs::Component
	{
		REGISTER_COMPONENT(Position)

	public:
		float x = 0.f;
		float y = 0.f;
	};
}
