#pragma once

#include "Component.h"

namespace core
{
	class Direction : public ecs::Component
	{
	public:
		float x = 0.f;
		float y = 0.f;
	};
}
