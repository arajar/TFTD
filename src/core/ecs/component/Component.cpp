#include "pch.h"
#include "Component.h"

namespace core
{
	namespace ecs
	{
		std::string Component::Type = COMPONENT_NAME(Component);

		Component::Component()
		{
			this->OnCreate();
		}

		Component::~Component()
		{
			this->OnDestroy();
		}
	}
}