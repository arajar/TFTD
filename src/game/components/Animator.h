#pragma once

#include "ecs/Component.h"

namespace ecs
{
	class Updatable : public core::ecs::Component
	{
	public:
		virtual void Update(sf::Time time) = 0;
	};
}
