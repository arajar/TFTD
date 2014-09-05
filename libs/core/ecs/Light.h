#pragma once

#include "ecs.h"

namespace core
{
	class ILight;

	namespace ecs
	{
		class Light : public Component
		{
		public:
			ILight* light;
		};
	}
}