#pragma once

namespace core
{
	namespace ecs
	{

#define COMPONENT_NAME(x) #x
#define REGISTER_COMPONENT(x) public:\
			static std::string Type;\
			virtual std::string GetType() {return COMPONENT_NAME(x);}


		class Component
		{
			REGISTER_COMPONENT(Component)

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