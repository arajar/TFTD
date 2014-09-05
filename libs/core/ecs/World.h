#pragma once
#include "ecs\Component.h"

namespace core
{
	namespace ecs
	{
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
			void Update(sf::Time deltaTime);
			void Render(sf::RenderTarget& target);
			void HandleEvents(sf::Keyboard::Key key, bool isPressed);

		public:
			const Entity::Id CreateEntity();
			void DeleteEntity(const Entity::Id& entity);

		public:
			template <typename C = Component>
			C* AddComponent(const Entity::Id& entity);

			template <typename C = Component>
			bool HasComponent(const Entity::Id& entity) const;

			template <typename C = Component>
			C* GetComponent(const Entity::Id& entity);

			template <typename C = Component>
			bool RemoveComponent(const Entity::Id& entity);

			template<typename A = Component>
			const std::vector<Entity::Id> GetEntitiesWith();

			template<typename A = Component, typename B = Component>
			const std::vector<Entity::Id> GetEntitiesWith();

		public:
			template<typename S>
			void AddSystem();

		private:
			typedef std::vector<Component*> ComponentArray;
			std::map<Entity::Id, ComponentArray> m_entities;

			std::vector<System*> m_systems;

		private:
			Entity::Id m_entityId;
		};
	}
}

// Template functions implementations
#include "World.inl"
