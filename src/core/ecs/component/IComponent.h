#pragma once

namespace core
{
	namespace ecs
	{
		class IComponent
		{
		public:
			IComponent() {};
			virtual ~IComponent() {};
		
		public:
			virtual void Update(Uint32 deltaTime) = 0;

		public:
			virtual void OnCreate() {};
			virtual void OnAttach() {};
			virtual void OnRemove() {};
			virtual void OnDestroy() {};
		};

		template <class C>
		class Component : public IComponent
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
		};
	}
}