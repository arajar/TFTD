#pragma once
///////////////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "config/Config.h"

///////////////////////////////////////////////////////////////////////////////

class Game : public core::Engine
{
public:
	Game(const std::string& name);
	virtual ~Game();

	Game(const Game&) = delete; // Disallow copying
	Game& operator=(const Game&) = delete; // Disallow copying

public:
	virtual bool Init() override;

public:
	virtual void HandleEvents(core::WindowEvent event) override;

protected:
	virtual void RenderFrame() override;

protected:
	bool InitGUI();
	static void GUI_RenderDrawLists(ImDrawList** const cmd_lists);

private:
	GameConfig m_gameConfig;

private:
	core::ecs::World m_world;

private:
	bool m_debugModeEnabled;
};

///////////////////////////////////////////////////////////////////////////////
