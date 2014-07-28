#pragma once

namespace core
{
	namespace ecs
	{
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
			virtual void Update(Uint32 deltaTime) = 0;

		public:
			virtual void OnCreate() {};
			virtual void OnAttach() {};
			virtual void OnRemove() {};
			virtual void OnDestroy() {};
		};
	}
}