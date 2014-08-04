#include "pch.h"
#include "World.h"

#include "Entity.h"
#include "System.h"

namespace core
{
	namespace ecs
	{
		World::World()
		{
		}

		World::~World()
		{
			m_newEntities.clear();
			m_entities.clear();
		}

		void World::Update(Uint32 deltaTime)
		{
			for (auto& logicSystem : m_logicSystems)
			{
				logicSystem->Process(deltaTime);
			}

			UpdateSystems();
		}

		void World::Render()
		{
			for (auto& renderSystem : m_renderSystems)
			{
				renderSystem->Process();
			}
		}

		void World::HandleEvents(const SDL_Event& event)
		{
			for (auto& eventSystem : m_eventSystems)
			{
				eventSystem->Process(event);
			}
		}

		Entity* World::CreateEntity(const std::string& name)
		{
			auto entity = new Entity(name);
			m_newEntities.push_back(entity);
			return entity;
		}

		void World::DeleteEntity(Entity* entity)
		{
			auto it = std::find(m_entities.begin(), m_entities.end(), entity);
			if (it != m_entities.end())
			{
				m_entities.erase(it);
			}
		}

		void World::AddSystem(System* system)
		{
			switch (system->GetType())
			{
			case SystemType::Logic:
				m_logicSystems.push_back(system);
				break;
			case SystemType::Render:
				m_renderSystems.push_back(system);
				break;
			case SystemType::EventHandler:
				m_eventSystems.push_back(system);
				break;
			default:
				throw new GameException("Unknown type for system");
				break;
			}
		}

		void World::UpdateSystems()
		{
			if (!m_newEntities.empty())
			{
				for (auto entity : m_newEntities)
				{
					for (auto system : m_logicSystems)
					{
						if (system->ValidateEntity(entity))
						{
							system->AddEntity(entity);
							m_entities.push_back(entity);
						}
					}

					for (auto system : m_renderSystems)
					{
						if (system->ValidateEntity(entity))
						{
							system->AddEntity(entity);
							m_entities.push_back(entity);
						}
					}

					for (auto system : m_eventSystems)
					{
						if (system->ValidateEntity(entity))
						{
							system->AddEntity(entity);
							m_entities.push_back(entity);
						}
					}
				}

				m_newEntities.clear();
			}
		}
	}
}