#include "pch.h"
#include "Game.h"
#include "config\GameConfig.h"
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

	m_world.AddSystem(new core::MovementSystem);
	auto e = m_world.CreateEntity("derp0");
	auto pos = e->AddComponent<core::Position>();
	auto dir = e->AddComponent<core::Direction>();

	pos->x = 10;
	dir->x = 1.3f;
	dir->y = 0.4f;

	core::fs::FileSystem fs("./Data");
	fs.Init();

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
