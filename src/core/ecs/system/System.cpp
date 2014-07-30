#include "pch.h"
#include "System.h"
#include "Entity.h"

namespace core
{
	namespace ecs
	{
		System::System()
			: m_type(SystemType::None)
			, m_priority(-1)
		{
		}

		System::~System()
		{
			m_entities.clear();
		}

		const SystemType System::GetType() const
		{
			return m_type;
		}

		const int System::GetPriority() const
		{
			return m_priority;
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

		bool System::Requires(const std::vector<Component*>& components) const
		{
			for (const auto& comp : components)
			{
				auto found = std::find(m_requirements.begin(), m_requirements.end(), comp->GetType());
				if (found != m_requirements.end())
				{
					return true;
				}
			}

			return false;
		}
	}
}