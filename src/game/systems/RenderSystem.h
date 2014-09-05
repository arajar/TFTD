#pragma once

#include "ecs/System.h"

namespace ecs
{
	class RenderSystem : public core::ecs::System
	{
	public:
		RenderSystem(core::ecs::World& world);

	public:
		virtual void Process(sf::RenderTarget& target) override;
	};

}