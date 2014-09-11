#pragma once

#include "ecs/System.h"

namespace ecs
{
	class RenderSystem : public core::ecs::System
	{
		NAME(RenderSystem)
	public:
		RenderSystem(core::ecs::World& world);

	public:
		virtual void Process(sf::RenderTarget& target) override;
	};

	class RenderDebugSystem : public core::ecs::System
	{
		NAME(RenderDebugSystem)
	public:
		RenderDebugSystem(core::ecs::World& world);
	
	public:
		virtual void Process(sf::RenderTarget& target) override;
	};
}