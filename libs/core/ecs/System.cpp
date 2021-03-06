#include "core.h"
#include "System.h"
#include "World.h"

namespace core
{
	namespace ecs
	{
		System::System(World& world)
			: m_world(world)
			, m_type(SystemType::None)
			, m_priority(-1)
		{
		}

		System::~System()
		{
		}

		SystemType System::GetType() const
		{
			return m_type;
		}

		int System::GetPriority() const
		{
			return m_priority;
		}
	}
}