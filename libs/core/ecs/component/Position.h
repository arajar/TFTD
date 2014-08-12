#pragma once

#include "Component.h"

namespace core
{
	class Position : public ecs::Component
	{
	public:
		float x = 0.f;
		float y = 0.f;
	};
}
