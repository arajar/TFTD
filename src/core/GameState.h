#pragma once

///////////////////////////////////////////////////////////////////////////////

class GameState
{
public:
	enum class GoToNext
	{
		MAIN_MENU,
		GAMEPLAY,
		END,
		NONE,
	};

public:
	virtual void Start() = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;
	virtual void Update(uint deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void End() = 0;
};

//////////////////////////////////////////////////////////////////////////

typedef std::shared_ptr<GameState> GameStatePtr;

//////////////////////////////////////////////////////////////////////////
