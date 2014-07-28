#pragma once

namespace core
{
	namespace ecs
	{
		class Entity;

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
			virtual const SystemType GetType() const = 0;

		public:
			virtual void Process(Uint32 deltaTime) = 0;

		public:
			bool AddEntity(Entity* entity);
			bool RemoveEntity(Entity* entity);

		protected:
			std::vector<Entity*> m_entities;
		};
	}
}