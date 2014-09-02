#pragma once
#include "ecs.h"
#include "World.h"

namespace core
{
	namespace ecs
	{
		template <typename C>
		C* World::AddComponent(const Entity::Id& entity)
		{
			if (!HasComponent<C>(entity))
			{
				C* comp = new C;
				m_entities[entity].push_back(comp);
				return comp;
			}

			return nullptr;
		}

		template <typename C>
		bool World::HasComponent(const Entity::Id& entity) const
		{
			auto it = m_entities.find(entity);
			if (it != m_entities.end())
			{
				auto comps = (*it).second;
				for (auto co : comps)
				{
					if (dynamic_cast<C*>(co))
					{
						return true;
					}
				}
			}

			return false;
		}

		template <typename C>
		C* World::GetComponent(const Entity::Id& entity)
		{
			if (m_entities.find(entity) != m_entities.end())
			{
				auto comps = m_entities[entity];
				for (auto& c : comps)
				{
					auto co = dynamic_cast<C*>(c);
					if (co != nullptr)
					{
						return co;
					}
				}
			}

			return nullptr;
		}

		template <typename C>
		bool World::RemoveComponent(const Entity::Id& entity)
		{
			if (m_entities.find(entity) != m_entities.end())
			{
				auto& comps = m_entities[entity];
				for (auto& c : comps)
				{
					auto co = dynamic_cast<C*>(c);
					comps.erase(co);
					return true;
				}
			}

			return false;
		}

		template<typename A>
		const std::vector<Entity::Id> World::GetEntitiesWith()
		{
			std::vector<Entity::Id> entities;

			auto itBegin = m_entities.begin();
			auto itEnd = m_entities.end();

			for (itBegin; itBegin != itEnd; itBegin++)
			{
				auto comp = (*itBegin).second;
				for (int i = 0; i < comp.size(); i++)
				{
					if (dynamic_cast<A*>(comp[i]))
					{
						entities.push_back((*itBegin).first);
					}
				}
			}

			return entities;
		}

		template<typename A, typename B>
		const std::vector<Entity::Id> World::GetEntitiesWith()
		{
			std::vector<Entity::Id> entities;

			auto itBegin = m_entities.begin();
			auto itEnd = m_entities.end();

			for (itBegin; itBegin != itEnd; itBegin++)
			{
				auto comp = (*itBegin).second;
				for (int i = 0; i < comp.size(); i++)
				{
					if (dynamic_cast<A*>(comp[i]) || dynamic_cast<B*>(comp[i]))
					{
						entities.push_back((*itBegin).first);
					}
				}
			}

			return entities;
		}

		template<typename S>
		void World::AddSystem()
		{
			auto sort = [](const System* a, const System* b)
			{
				return a->GetPriority() < b->GetPriority();
			};

			m_systems.push_back(new S(*this));
			std::sort(m_systems.begin(), m_systems.end(), sort);
		}
	}
}