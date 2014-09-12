#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
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

///////////////////////////////////////////////////////////////////////////////

class GameState : public State
{
public:
	GameState(core::ecs::World& world, core::FileSystem& fs)
		: State(world)
		, m_fs(fs)
	{		
	}

	virtual ~GameState() {}

	virtual void Start() override
	{
		m_debugText.setFont(core::Engine::DEBUG_FONT);

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
	}

	virtual void Resume() override
	{
		m_world.AddSystem<ecs::InputSystem>();
		m_world.AddSystem<ecs::MovementSystem>();
		m_world.AddSystem<ecs::RenderSystem>();
		m_world.AddSystem<ecs::AnimationSystem>();
		m_world.AddSystem<ecs::LightSystem>()->SetGlobalAmbientColor(sf::Color(50, 20, 20));
	}

	virtual void Suspend() override
	{
		m_world.RemoveSystem<ecs::InputSystem>();
		m_world.RemoveSystem<ecs::MovementSystem>();
		m_world.RemoveSystem<ecs::RenderSystem>();
		m_world.RemoveSystem<ecs::AnimationSystem>();
		m_world.RemoveSystem<ecs::LightSystem>();
	}

	virtual void HandleEvents(core::WindowEvent event) override
	{
		State::HandleEvents(event);
	}

	virtual void Update(sf::Time deltaTime) override
	{
		State::Update(deltaTime);
	}

	virtual void Render(sf::RenderTarget& target) override
	{
		State::Render(target);
	}

	void RenderDebug(sf::RenderTarget& target) override
	{
		m_debugText.setString("Game");
		target.draw(m_debugText);
	}

	virtual void End() override
	{
	}

private:
	core::FileSystem& m_fs;
};

//////////////////////////////////////////////////////////////////////////

