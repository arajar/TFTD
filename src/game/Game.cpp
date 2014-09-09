#include "pch.h"
#include "Game.h"
#include "config/Config.h"
#include "filesystem/filesystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "LightSystem.h"
#include "AnimationSystem.h"
#include "Sprite.h"
#include "Position.h"
#include "Transform.h"
#include "InputController.h"
#include "Skeleton2D.h"
#include "LightBlocker.h"

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

	{
		auto entity = m_world.CreateEntity();
		auto p = m_world.AddComponent<ecs::Transform>(entity);
		m_world.AddComponent<ecs::Direction>(entity);
		m_world.AddComponent<ecs::InputController>(entity);
		auto s = m_world.AddComponent<ecs::Skeleton2D>(entity);
		s->Init("goblin", m_fs["goblins-ffd.atlas"], m_fs["goblins-ffd.json"]);
		s->SetAnimation("walk");
		s->Scale(sf::Vector2f(0.5f, 0.5f));
		p->SetPosition(glm::vec3(100, 100, 0));

		core::OmniLight* omni = new core::OmniLight();
		omni->SetPosition(glm::vec2(375, 275));
		omni->SetIntensity(255);
		omni->SetRadius(400.f);
		omni->SetQuality(LightQuality::ULTRA);
		omni->SetColor(sf::Color::White);

		m_world.AddComponent<core::ecs::Light>(entity, omni);
	}

	/*
	{
		auto entity = m_world.CreateEntity();
		auto p = m_world.AddComponent<ecs::Transform>(entity);
		m_world.AddComponent<ecs::Direction>(entity);
		auto s = m_world.AddComponent<ecs::Skeleton2D>(entity);
		s->Init("goblingirl", m_fs["goblins-ffd.atlas"], m_fs["goblins-ffd.json"]);
		s->SetAnimation("walk");
		p->SetPosition(glm::vec3(300, 300, 0));

		s->Dettach("left hand item");

		auto b = m_world.AddComponent<ecs::LightBlocker>(entity);
		
		core::Wall w;
		w.pt1 = glm::vec2(100, 100);
		w.pt2 = glm::vec2(100, 300);
		b->wall.push_back(w);

		core::Wall w1;
		w1.pt1 = glm::vec2(100, 100);
		w1.pt2 = glm::vec2(300, 100);
		b->wall.push_back(w1);

		core::Wall w2;
		w2.pt1 = glm::vec2(300, 100);
		w2.pt2 = glm::vec2(300, 300);
		b->wall.push_back(w2);
	}
	*/

	m_world.AddSystem<ecs::InputSystem>();
	m_world.AddSystem<ecs::MovementSystem>();
	m_world.AddSystem<ecs::RenderSystem>();
	m_world.AddSystem<ecs::AnimationSystem>();
	//m_world.AddSystem<ecs::LightSystem>()->SetGlobalAmbientColor(sf::Color(50, 20, 20));

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

	if (key == sf::Keyboard::F1 && isPressed)
	{
		if (m_world.HasSystem<ecs::RenderDebugSystem>())
		{
			m_world.RemoveSystem<ecs::RenderDebugSystem>();
		}
		else
		{
			m_world.AddSystem<ecs::RenderDebugSystem>();
		}
	}
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