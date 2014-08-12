#pragma once

#include "ecs/system/System.h"

namespace core
{
	class RenderSystem : public ecs::System
	{
	public:
		RenderSystem();

	public:
		virtual void Process() override;
	};

}