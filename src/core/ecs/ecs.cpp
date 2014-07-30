#include "pch.h"

#include "ecs.h"

namespace core
{
	std::string ecs::Component::Type = COMPONENT_NAME(ecs::Component);
	std::string Direction::Type = COMPONENT_NAME(Direction);
	std::string Position::Type = COMPONENT_NAME(Position);
	std::string Transform::Type = COMPONENT_NAME(Transform);
}