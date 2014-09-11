#include "core.h"
#include "World.h"

#include "System.h"
#include "pugixml.hpp"

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

		void World::Update(sf::Time deltaTime)
		{
			for (auto& system : m_systems)
			{
				if (system->GetType() == SystemType::Logic)
				{
					system->Process(deltaTime);
				}
			}
		}

		void World::Render(sf::RenderTarget& target)
		{
			for (auto& system : m_systems)
			{
				if (system->GetType() == SystemType::Render)
				{
					system->Process(target);
				}
			}
		}

		void World::HandleEvents(core::WindowEvent event)
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

		bool World::Save() const
		{
			return Serialize("world.w");
		}

		bool World::Load() const
		{
			return Deserialize("world.w");
		}

		bool World::Serialize(std::string const& file) const
		{
			pugi::xml_document doc;
			auto parent = doc.append_child("World");
			parent.append_attribute("version").set_value("0.0.1");

			auto sysNode = parent.append_child("Systems");
			for (auto system : m_systems)
			{
				auto s = sysNode.append_child("System");
				s.append_attribute("name").set_value(system->GetName().c_str());
			}

			return doc.save_file(file.c_str());
		}

		bool World::Deserialize(std::string const& file) const
		{
			return true;
		}
	}
}