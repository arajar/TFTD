#pragma once
#include "Component.h"

namespace core
{
	namespace ecs
	{
		class Entity;
		class Component;

		enum class SystemType
		{
			Logic,
			Render,
			None,
		};

		class System
		{
		public:
			System();
			virtual ~System();

		public:
			virtual const SystemType GetType() const;
			virtual const int GetPriority() const;

		public:
			virtual void Process(Uint32 deltaTime) = 0;

		public:
			bool AddEntity(Entity* entity);
			bool RemoveEntity(Entity* entity);

		public:
			template<typename C = Component>
			void AddRequirement()
			{
				m_requirements.push_back(C::Type);
			}

			bool Requires(std::vector<Component*> requirements) const;

		protected:
			std::vector<Entity*> m_entities;
			std::vector<std::string> m_requirements;

			SystemType m_type;
			int m_priority;
		};
	}
}