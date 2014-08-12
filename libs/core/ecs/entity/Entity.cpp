#include "core.h"
#include "Entity.h"

namespace core
{
	namespace ecs
	{
		Entity::Entity(const std::string& name)
			: m_name(name)
		{
		}

		Entity::~Entity()
		{
			for (auto comp : m_components)
			{
				comp->OnRemove();
			}

			m_components.clear();
		}

		const std::string& Entity::GetName() const
		{
			return m_name;
		}

		const std::vector<Component*>& Entity::GetComponents()
		{
			return m_components;
		}
	}
}