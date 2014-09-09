#pragma once

#include "components/Renderable.h"

namespace ecs
{
	class core::Image;

	class Sprite : public ecs::Renderable
	{
	public:
		static std::string Type;

	public:
		Sprite();
		explicit Sprite(core::Image* image);
		virtual ~Sprite();

	public:
		void SetImage(core::Image* img) { m_image = img; }
		virtual void Render(sf::RenderTarget& tex) override;
		virtual void SetPosition(const glm::vec3& pos) override;

	private:
		core::Image* m_image;
	};
}
