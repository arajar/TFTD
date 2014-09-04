#pragma once
///////////////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "config/Config.h"

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
	virtual void HandleEvents(sf::Keyboard::Key key, bool isPressed) override;
	virtual void Update(sf::Time deltaTime) override;

protected:
	virtual void RenderFrame() override;

protected:
	bool InitGUI();
	static void GUI_RenderDrawLists(ImDrawList** const cmd_lists);

private:
	GameConfig m_gameConfig;

private:
	core::ecs::World m_world;
};

///////////////////////////////////////////////////////////////////////////////
