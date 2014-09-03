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

	void InputSystem::Process(const SDL_Event& event)
	{
		for (auto e : m_world.GetEntitiesWith<ecs::InputController, ecs::Direction>())
		{
			auto &dir = *m_world.GetComponent<ecs::Direction>(e);

			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					dir.x = -1;
					break;
				case SDLK_RIGHT:
					dir.x = 1;
					break;
				case SDLK_UP:
					dir.y = -1;
					break;
				case SDLK_DOWN:
					dir.y = 1;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
				case SDLK_RIGHT:
					dir.x = 0.f;
					break;
				case SDLK_UP:
				case SDLK_DOWN:
					dir.y = 0.f;
					break;
				}
				break;
			}
		}
	}
}