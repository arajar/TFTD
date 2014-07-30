#pragma once

namespace core
{
	namespace ecs
	{

#define COMPONENT_NAME(x) #x

		class Component
		{
		public:
			static std::string Type;

		public:
			Component();
			virtual ~Component();
			
		public:
			virtual void Update(Uint32 deltaTime) {};

		public:
			virtual void OnCreate() {};
			virtual void OnAttach() {};
			virtual void OnRemove() {};
			virtual void OnDestroy() {};
		};
	}
}