#include "core.h"
#include "StateManager.h"

//////////////////////////////////////////////////////////////////////////

StateManager::StateManager()
{
}

//////////////////////////////////////////////////////////////////////////

void StateManager::Update(sf::Time deltaTime)
{
	m_states.front()->Update(deltaTime);
}

//////////////////////////////////////////////////////////////////////////

void StateManager::Render(sf::RenderTarget& target)
{
	m_states.front()->Render(target);
}

//////////////////////////////////////////////////////////////////////////

void StateManager::HandleEvents(sf::Keyboard::Key key, bool isPressed)
{
	m_states.front()->HandleEvents(key, isPressed);
}

//////////////////////////////////////////////////////////////////////////

State* StateManager::GetCurrentState()
{
	return m_states.front();
}

//////////////////////////////////////////////////////////////////////////

bool StateManager::PopState()
{
	if (!m_states.empty())
	{
		auto lastState = m_states.back();
		lastState->Suspend();
		lastState->End();
		m_states.pop_back();
	}

	return m_states.empty();
}

//////////////////////////////////////////////////////////////////////////

void StateManager::PopAllStates()
{
	if (!m_states.empty())
	{
		auto lastState = m_states.back();
		lastState->Suspend();
	}

	while (!m_states.empty())
	{
		auto lastState = m_states.back();
		lastState->End();
		m_states.pop_back();
	}
}

//////////////////////////////////////////////////////////////////////////
