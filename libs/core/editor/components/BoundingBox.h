#pragma once
#include <ecs/Component.h>

namespace editor
{
	class BoundingBox : public core::ecs::Component
	{
	public:
		glm::vec2 upperLeft;
		glm::vec2 lowerRight;
	};
}