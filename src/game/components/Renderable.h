#pragma once

#include "ecs/Component.h"

namespace ecs
{
	class Renderable : public core::ecs::Component
	{
	public:
		virtual void Render(sf::RenderTarget& tex) = 0;
		virtual void RenderDebug(sf::RenderTarget& tex) {};
		virtual void SetPosition(const glm::vec3& pos) = 0;
	};
}
