#pragma once

namespace core
{
	namespace ecs
	{

#define COMPONENT_NAME(x) #x

		class Component
		{
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
			virtual void OnTick(Uint32 deltaTime) {};

		public:
			virtual void OnCreate() {};
			virtual void OnAttach() {};
			virtual void OnRemove() {};
			virtual void OnDestroy() {};
		};
	}
}