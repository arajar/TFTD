#pragma once

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
			System(World& world);
			virtual ~System();

		public:
			virtual const SystemType GetType() const;
			virtual const int GetPriority() const;

		public:
			virtual void Process() {};
			virtual void Process(Uint32 deltaTime) {};
			virtual void Process(const SDL_Event& event) {};

		protected:
			World& m_world;

			SystemType m_type;
			int m_priority;
		};
	}
}