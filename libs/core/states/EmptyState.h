#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <lights/OmniLight.h>

///////////////////////////////////////////////////////////////////////////////

class StateDefault : public State
{
public:
	virtual ~StateDefault() {}

	virtual void Start() override
	{
		m_debugText.setFont(core::Engine::DEBUG_FONT);
	}

	virtual void Resume() override
	{}

	virtual void Suspend() override
	{}

	virtual void HandleEvents(const core::WindowEvent event) override
	{}

	virtual void Update(sf::Time deltaTime) override
	{}

	virtual void Render(sf::RenderTarget& target) override
	{}

	void RenderDebug(sf::RenderTarget& target) override
	{
		m_debugText.setString("Default");
		target.draw(m_debugText);
	}

	virtual void End() override
	{}
};

//////////////////////////////////////////////////////////////////////////

