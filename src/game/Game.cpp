#include "pch.h"
#include "Game.h"
#include "config/Config.h"
#include "filesystem/filesystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Sprite.h"
#include "Position.h"
#include "InputController.h"

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
	m_world.AddComponent<ecs::Direction>(entity);
	m_world.AddComponent<ecs::InputController>(entity);
	auto s = m_world.AddComponent<ecs::Sprite>(entity);
	auto img = core::ContentManager::GetInstance()->Get<core::Image>("p1_stand.png");
	s->SetImage(img);

	p->x = 10;
	p->y = 10;

	m_world.AddSystem<ecs::InputSystem>();
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

void Game::HandleEvents(sf::Keyboard::Key key, bool isPressed)
{
	m_world.HandleEvents(key, isPressed);
}

//////////////////////////////////////////////////////////////////////////

void Game::Update(sf::Time deltaTime)
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
