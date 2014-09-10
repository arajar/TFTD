#pragma once
#include <Events.h>

namespace core
{
	namespace ecs
	{
		class World;

		enum class SystemType
		{
			Logic,
			Render,
			EventHandler,
			None,
		};

		class System
		{
			ID(System);
		public:
			explicit System(World& world);
			virtual ~System();

		public:
			virtual SystemType GetType() const;
			virtual int GetPriority() const;

		public:
			virtual void Process(sf::RenderTarget& target) {};
			virtual void Process(sf::Time deltaTime) {};
			virtual void Process(const core::WindowEvent event) {};

		protected:
			World& m_world;

			SystemType m_type;
			int m_priority;
		};
	}
}