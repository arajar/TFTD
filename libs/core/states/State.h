#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

///////////////////////////////////////////////////////////////////////////////

class State
{
public:
	virtual ~State() {}

	virtual void Start() = 0;
	virtual void Resume() = 0;
	virtual void Suspend() = 0;
	virtual void HandleEvents(sf::Keyboard::Key key, bool isPressed) = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void End() = 0;
};

//////////////////////////////////////////////////////////////////////////

typedef std::shared_ptr<State> StatePtr;

//////////////////////////////////////////////////////////////////////////
