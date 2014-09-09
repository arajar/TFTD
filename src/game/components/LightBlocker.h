#pragma once

#include "lights/Light.h"
#include "ecs/Component.h"

namespace ecs
{
	class LightBlocker : public core::ecs::Component
	{
	public:
		std::vector<core::Wall> wall;
	};
}
