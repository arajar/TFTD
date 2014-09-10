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
	void RenderDebug(sf::RenderTarget& target);
	void HandleEvents(const core::WindowEvent event);

public:
	State* GetCurrentState();

	template<typename S>
	S* GetState();

	template<typename S, class... _Types>
	void SetState(_Types&&... _Args);

	template<typename S, class... _Types>
	void PushState(_Types&&... _Args);

	bool PopState();
	void PopAllStates();

	template<typename S>
	bool IsStateInStack() const;

	template<typename S>
	bool CurrentStateIs() const;

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

template <typename S, class ... _Types>
void StateManager::SetState(_Types&&... _Args)
{
	PopAllStates();
	PushState<S>(std::forward<_Types>(_Args)...);
}

//////////////////////////////////////////////////////////////////////////

template <typename S, class ... _Types>
void StateManager::PushState(_Types&&... _Args)
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
			m_states.push_back(state);
			state->Resume();
			return;
		}
	}

	S* state = new S(_Args...);
	m_states.push_back(state);
	state->Start();
	state->Resume();
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

template <typename S>
bool StateManager::CurrentStateIs() const
{
	return dynamic_cast<S*>(m_states.back()) != nullptr;
}

//////////////////////////////////////////////////////////////////////////
