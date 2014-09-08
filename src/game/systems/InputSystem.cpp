#include "pch.h"
#include "InputSystem.h"
#include "Position.h"
#include "InputController.h"

namespace ecs
{
	InputSystem::InputSystem(core::ecs::World& world)
		: System(world)
	{
		m_type = core::ecs::SystemType::EventHandler;
	}

	void InputSystem::Process(sf::Keyboard::Key key, bool isPressed)
	{
		for (auto e : m_world.GetEntitiesWith<ecs::InputController, ecs::Direction>())
		{
			auto &dir = *m_world.GetComponent<ecs::Direction>(e);

			float x = 0;
			float y = 0;
			switch (key)
			{
			case sf::Keyboard::Left:
				x = isPressed ? -1.0f : 0.0f;
				break;
			case sf::Keyboard::Right:
				x = isPressed ? 1.0f : 0.0f;
				break;
			case sf::Keyboard::Up:
				y = isPressed ? -1.0f : 0.0f;
				break;
			case sf::Keyboard::Down:
				y = isPressed ? 1.0f : 0.0f;
				break;
			}

			dir.dir = glm::vec3(x, y, 0.f);
		}
	}
}
