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

	void Sprite::Render()
	{
		m_image->Render();
	}

	void Sprite::SetPosition(const glm::ivec2& pos)
	{
		m_image->SetPosition(pos);
	}
}