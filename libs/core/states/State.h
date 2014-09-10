#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Events.h>

///////////////////////////////////////////////////////////////////////////////

class State
{
public:
	State(core::ecs::World& world)
		: m_world(world)	{}

	virtual ~State() {}

	virtual void Start() = 0;
	virtual void Resume() = 0;
	virtual void Suspend() = 0;
	virtual void End() = 0;

public:
	virtual void HandleEvents(const core::WindowEvent event)
	{
		m_world.HandleEvents(event);
	}

	virtual void Update(sf::Time deltaTime)
	{
		m_world.Update(deltaTime);
	}

	virtual void Render(sf::RenderTarget& target)
	{
		m_world.Render(target);
	}

	virtual void RenderDebug(sf::RenderTarget& target) = 0;

protected:
	core::ecs::World& m_world;

protected:
	sf::Text m_debugText;
};

//////////////////////////////////////////////////////////////////////////

typedef std::shared_ptr<State> StatePtr;

//////////////////////////////////////////////////////////////////////////
