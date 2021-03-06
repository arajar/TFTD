#include "pch.h"
#include "Sprite.h"
#include "resources/Image.h"

namespace ecs
{
	Sprite::Sprite()
		: m_image(nullptr)
	{
	}

	Sprite::Sprite(core::Image* image)
		: m_image(image)
	{
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Render(sf::RenderTarget& tex)
	{
		m_image->Render(tex);
	}

	void Sprite::SetPosition(const glm::vec3& pos)
	{
		m_image->SetPosition(pos);
	}
}