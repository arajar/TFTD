#include "pch.h"
#include "Game.h"
#include "config/Config.h"
#include "filesystem/filesystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "Sprite.h"
#include "Position.h"
#include "Direction.h"

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

	auto entity = m_world.CreateEntity();
	auto p = m_world.AddComponent<ecs::Position>(entity);
	auto s = m_world.AddComponent<ecs::Sprite>(entity);
	auto img = core::ContentManager::GetInstance()->Get<core::Image>("Goblin.png");
	s->SetImage(img);

	bool aaa = m_world.HasComponent<ecs::Direction>(entity);

	p->x = 10;
	p->y = 10;

	m_world.AddSystem<ecs::MovementSystem>();
	m_world.AddSystem<ecs::RenderSystem>();

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

bool Game::InitGUI()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
