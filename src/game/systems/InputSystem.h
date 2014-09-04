#pragma once

#include "ecs/System.h"

namespace ecs
{
	class InputSystem : public core::ecs::System
	{
	public:
		InputSystem(core::ecs::World& world);

	public:
		virtual void Process(sf::Keyboard::Key key, bool isPressed) override;
	};
}