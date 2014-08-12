#include "pch.h"
#include "Game.h"
#include "Config.h"
#include "filesystem.h"


//////////////////////////////////////////////////////////////////////////

Game::Game()
: m_gameConfig("config.cfg")
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

	bool initialized = false;
	if (m_gameConfig.Init())
	{
		Engine::Resize(m_gameConfig["screen.width"], m_gameConfig["screen.height"]);
		initialized = true;
	}

	return initialized;
}

//////////////////////////////////////////////////////////////////////////

void Game::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_QUIT)
	{
		m_running = false;
		return;
	}

	m_world.HandleEvents(event);
}

//////////////////////////////////////////////////////////////////////////

void Game::Update(Uint32 deltaTime)
{
	Engine::Update(deltaTime);
	m_world.Update(deltaTime);
}

//////////////////////////////////////////////////////////////////////////

void Game::RenderFrame()
{
	m_world.Render();
}

//////////////////////////////////////////////////////////////////////////
