#pragma once

#include "ecs/System.h"

namespace ecs
{
	class InputSystem : public core::ecs::System
	{
		NAME(InputSystem)

	public:
		InputSystem(core::ecs::World& world);

	public:
		virtual void Process(const core::WindowEvent event) override;
	};
}