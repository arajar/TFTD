#include "pch.h"
#include "Game.h"
#include "config/Config.h"
#include "filesystem/filesystem.h"

#include "GameState.h"
#include "editor/state/EditorState.h"

//////////////////////////////////////////////////////////////////////////

Game::Game(const std::string& name)
	: core::Engine(name)
	, m_gameConfig("config.cfg")
	, m_debugModeEnabled(false)
{
}

//////////////////////////////////////////////////////////////////////////

Game::~Game()
{
}

//////////////////////////////////////////////////////////////////////////

bool Game::Init()
{
	Engine::Init();

	m_stateMgr.SetState<GameState>(m_world, m_fs);

	bool initialized = false;
	if (m_gameConfig.Init())
	{
		Engine::Resize(m_gameConfig["screen.width"], m_gameConfig["screen.height"]);
		initialized = true;
	}

	return initialized;
}

//////////////////////////////////////////////////////////////////////////

void Game::HandleEvents(const core::WindowEvent windowEvent)
{
	Engine::HandleEvents(windowEvent);
	m_stateMgr.HandleEvents(windowEvent);
	
	bool keyPressed = false;

	switch (windowEvent.event.type)
	{
	case sf::Event::KeyPressed:
		keyPressed = true;
		break;
	case sf::Event::KeyReleased:
		keyPressed = false;
		break;
	default: break;
	}

	auto key = windowEvent.event.key.code;

	if (key == sf::Keyboard::F1 && keyPressed)
	{
		if (m_world.HasSystem<ecs::RenderDebugSystem>())
		{
			m_world.RemoveSystem<ecs::RenderDebugSystem>();
			m_debugModeEnabled = false;
		}
		else
		{
			m_world.AddSystem<ecs::RenderDebugSystem>();
			m_debugModeEnabled = true;
		}
	}
	else if (key == sf::Keyboard::F5 && keyPressed)
	{
		if (m_stateMgr.CurrentStateIs<editor::EditorState>())
		{
			m_stateMgr.PopState();
			m_stateMgr.PushState<GameState>(m_world, m_fs);
		}
		else
		{
			m_stateMgr.PushState<editor::EditorState>(m_world, m_fs["tileset_01.xml"]);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void Game::RenderFrame()
{
	if (m_debugModeEnabled)
	{
		m_stateMgr.RenderDebug(m_renderTarget);
	}
}

//////////////////////////////////////////////////////////////////////////

bool Game::InitGUI()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////