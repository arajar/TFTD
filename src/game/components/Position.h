#pragma once

#include "ecs/Component.h"

namespace ecs
{
	class Position : public core::ecs::Component
	{
	public:
		glm::vec3 pos;
	};

	class Direction : public core::ecs::Component
	{
	public:
		glm::vec3 dir;
	};
}
