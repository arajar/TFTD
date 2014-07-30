#pragma once

#include "System.h"

namespace core
{
	class RenderSystem : public ecs::System
	{
	public:
		RenderSystem();

	public:
		virtual void Process(Uint32 deltaTime) override;
	};

}