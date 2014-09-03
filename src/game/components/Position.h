#pragma once

#include "ecs/Component.h"

namespace ecs
{
	class Position : public core::ecs::Component
	{
	public:
		float x = 0.f;
		float y = 0.f;
	};

	class Direction : public core::ecs::Component
	{
	public:
		float x = 0.f;
		float y = 0.f;
	};
}
