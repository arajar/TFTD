#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

///////////////////////////////////////////////////////////////////////////////

class StateDefault : public State
{
public:
	virtual ~StateDefault() {}

	virtual void Start() override
	{}

	virtual void Resume() override
	{}

	virtual void Suspend() override
	{}

	virtual void HandleEvents(sf::Keyboard::Key key, bool isPressed) override
	{}

	virtual void Update(sf::Time deltaTime) override
	{}

	virtual void Render(sf::RenderTarget& target) override
	{}

	virtual void End() override
	{}
};

//////////////////////////////////////////////////////////////////////////

