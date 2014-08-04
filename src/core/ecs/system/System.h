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
			EventHandler,
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
			virtual void Process() {};
			virtual void Process(Uint32 deltaTime) {};
			virtual void Process(const SDL_Event& event) {};

		public:
			bool AddEntity(Entity* entity);
			virtual bool ValidateEntity(const Entity* entity) const = 0;
			bool RemoveEntity(Entity* entity);

		protected:
			std::vector<Entity*> m_entities;
			std::vector<std::string> m_requirements;

			SystemType m_type;
			int m_priority;
		};
	}
}