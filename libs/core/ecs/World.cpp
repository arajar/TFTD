#include "core.h"
#include "World.h"

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
			m_entities.clear();
		}

		void World::Update(Uint32 deltaTime)
		{
			for (auto& system : m_systems)
			{
				if (system->GetType() == SystemType::Logic)
				{
					system->Process(deltaTime);
				}
			}
		}

		void World::Render()
		{
			for (auto& system : m_systems)
			{
				if (system->GetType() == SystemType::Render)
				{
					system->Process();
				}
			}
		}

		void World::HandleEvents(const SDL_Event& event)
		{
			for (auto& system : m_systems)
			{
				if (system->GetType() == SystemType::EventHandler)
				{
					system->Process(event);
				}
			}
		}

		const Entity::Id World::CreateEntity()
		{
			auto newEntity = Entity::Id(++m_entityId);
			m_entities[newEntity].reserve(0);
			return newEntity;
		}

		void World::DeleteEntity(const Entity::Id& entity)
		{
			auto found = m_entities.find(entity);
			if (found != m_entities.end())
			{
				auto comp = m_entities[entity];
				for (auto c : comp)
				{
					c->OnRemove();
					delete c;
				}

				comp.clear();
				m_entities.erase(found);
			}
		}
	}
}