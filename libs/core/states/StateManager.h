#pragma once
#include "State.h"

///////////////////////////////////////////////////////////////////////////////

class StateManager
{
public:
	StateManager();
	virtual ~StateManager() {}

public:
	void Update(sf::Time deltaTime);
	void Render(sf::RenderTarget& target);
	void HandleEvents(sf::Keyboard::Key key, bool isPressed);

public:
	State* GetCurrentState();

	template<typename S>
	S* GetState();

	template<typename S>
	void SetState();

	template<typename S>
	void PushState();
	
	bool PopState();
	void PopAllStates();
	
	template<typename S>
	bool IsStateInStack() const;

public:
	std::vector<State*> m_states;
};

//////////////////////////////////////////////////////////////////////////

template <typename S>
S* StateManager::GetState()
{
	for (auto state : m_states)
	{
		S* s = dynamic_cast<S*>(state);
		if (s != nullptr)
		{
			return s;
		}
	}

	return nullptr;
}

//////////////////////////////////////////////////////////////////////////

template <typename S>
void StateManager::SetState()
{
	PopAllStates();
	PushState<S>();
}

//////////////////////////////////////////////////////////////////////////

template <typename S>
void StateManager::PushState()
{
	if (!m_states.empty())
	{
		auto currentState = GetCurrentState();
		if (currentState != nullptr)
		{
			currentState->Suspend();
		}

		if (IsStateInStack<S>())
		{
			auto state = GetState<S>();
			state->Resume();
		}
	}
	else
	{
		auto state = new S;
		m_states.push_back(state);
		state->Start();
	}
}

//////////////////////////////////////////////////////////////////////////

template <typename S>
bool StateManager::IsStateInStack() const
{
	for (auto state : m_states)
	{
		if (dynamic_cast<S*>(state))
		{
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
