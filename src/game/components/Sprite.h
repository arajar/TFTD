#pragma once

#include "ecs/Component.h"

namespace ecs
{
	class core::Image;

	class Sprite : public core::ecs::Component
	{
	public:
		static std::string Type;

	public:
		Sprite();
		Sprite(core::Image* image);
		virtual ~Sprite();

	public:
		void SetImage(core::Image* img) { m_image = img; }
		void Render();
		void SetPosition(const glm::ivec2& pos);

	private:
		core::Image* m_image;
	};
}
