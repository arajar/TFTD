#pragma once
#include "IComponent.h"

namespace core
{
	namespace ecs
	{
		class Entity
		{
		public:
			Entity(const std::string& name);
			virtual ~Entity();

		public:
			virtual void Init() = 0;
			virtual void Update(Uint32 deltaTime);

		public:
			const std::string& GetName() const;

		public:
			template <typename C = Component>
			bool AddComponent()
			{
				if (m_components.size() < s_maxComponents)
				{
					m_components.push_back(new C());
					return true;
				}

				return false;
			}

			template <typename C = Component>
			bool HasComponent() const
			{
				for (auto& component : m_components)
				{
					if (reinterpret_cast<C*>(component))
					{
						return true;
					}
				}

				return false;
			}

			template <typename C = Component>
			C* GetComponent()
			{
				for (auto& component : m_components)
				{
					C* comp = reinterpret_cast<C*>(component);
					if (comp)
					{
						return comp;
					}
				}
				
				return nullptr;
			}

			template <typename C = Component>
			bool RemoveComponent()
			{
				auto it = m_components.begin();
				auto end = m_components.end();

				for (it; it != end; it++)
				{
					if (reinterpret_cast<C*>(*it))
					{
						(*it)->OnRemove();
						m_components.erase(it);
						return true;
					}
				}

				return false;
			}

		protected:
			static const unsigned int s_maxComponents = 64;
			std::vector<Component*> m_components;

		protected:
			std::string m_name;
		};
	}
}