#pragma once

namespace core
{
	namespace ecs
	{
		class Entity;
		class EntityTemplate;
		class System;

		class World
		{
		public:
			World();
			~World();

			// Explicitly disallow copying this class
			World(const World& copy) = delete;

		public:
			void Update(Uint32 deltaTime);
			void Render();

		public:
			Entity* CreateEntity(const std::string& name);
			void DeleteEntity(Entity* entity);

		public:
			void AddSystem(System* system);

		private:
			void UpdateSystems();
			
		private:
			std::vector<Entity*> m_newEntities;
			std::vector<Entity*> m_entities;
			std::vector<System*> m_logicSystems;
			std::vector<System*> m_renderSystems;

		};
	}
}