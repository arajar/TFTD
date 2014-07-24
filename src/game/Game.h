#pragma once
///////////////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "config\GameConfig.h"

///////////////////////////////////////////////////////////////////////////////

class Game : public core::Engine
{
public:
	Game();
	virtual ~Game();

	Game(const Game&) = delete; // Disallow copying
	Game& operator=(const Game&) = delete; // Disallow copying

public:
	bool Init();

public:
	virtual void HandleEvents(const SDL_Event& event) override;
	virtual void Update(Uint32 deltaTime) override;

protected:
	virtual void RenderFrame() override;

private:
	GameConfig m_gameConfig;

};

///////////////////////////////////////////////////////////////////////////////
