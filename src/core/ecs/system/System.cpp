#include "pch.h"
#include "System.h"
#include "Entity.h"

namespace core
{
	namespace ecs
	{
		System::System()
		{
		}

		System::~System()
		{
			m_entities.clear();
		}

		bool System::AddEntity(Entity* entity)
		{
			// Check if the entity is already added on the system
			if (std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end())
			{
				m_entities.push_back(entity);
				return true;
			}

			return false;
		}

		bool System::RemoveEntity(Entity* entity)
		{
			auto found = std::find(m_entities.begin(), m_entities.end(), entity);
			if (found != m_entities.end())
			{
				m_entities.erase(found);
				return true;
			}
	
			return false;
		}
	}
}