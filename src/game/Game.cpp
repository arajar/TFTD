#include "pch.h"
#include "Game.h"
#include "config/Config.h"
#include "filesystem/filesystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "LightSystem.h"
#include "Sprite.h"
#include "Position.h"
#include "InputController.h"

#include "lights/OmniLight.h"
#include "lights/SpotLight.h"

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

	core::OmniLight* omni = new core::OmniLight();
	omni->SetPosition(sf::Vector2f(375, 275));
	omni->SetIntensity(255.f);
	omni->SetRadius(256.f);
	omni->SetQuality(LightQuality::ULTRA);
	omni->SetColor(sf::Color::White);

	m_world.AddComponent<core::ecs::Light>(entity, omni);

	m_world.AddSystem<ecs::InputSystem>();
	m_world.AddSystem<ecs::MovementSystem>();
	m_world.AddSystem<ecs::RenderSystem>();
	m_world.AddSystem<ecs::LightSystem>()->SetGlobalAmbientColor(sf::Color(0, 0, 0));

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
	m_world.Render(m_renderTarget);
}

//////////////////////////////////////////////////////////////////////////

bool Game::InitGUI()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
