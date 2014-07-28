#include "pch.h"
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

		void Entity::Update(Uint32 deltaTime)
		{
			for (auto comp : m_components)
			{
				comp->Update(deltaTime);
			}
		}

		const std::string& Entity::GetName() const
		{
			return m_name;
		}
	}
}