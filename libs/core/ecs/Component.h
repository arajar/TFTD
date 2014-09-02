#pragma once

#include "ecs.h"

namespace core
{
	namespace ecs
	{
		struct Entity
		{
			ID(Entity);
		};

		class Component
		{
			ID(Component);

		public:
			Component()
			{
				this->OnCreate();
			}

			virtual ~Component()
			{
				this->OnDestroy();
			}

		public:
			virtual void OnCreate() {};
			virtual void OnAttach() {};
			virtual void OnRemove() {};
			virtual void OnDestroy() {};

		};
	}
}