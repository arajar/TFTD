#include "core.h"
#include "Image.h"

namespace core
{
	Image::Image(const std::string& name)
		: m_name(name)
		, m_sprite(sf::Sprite())
	{
	}

	Image::~Image()
	{
	}

	bool Image::Load()
	{
		bool b = m_tex.loadFromFile(m_name);
		if (b)
		{
			m_sprite.setTexture(m_tex);
		}
		
		return b;
	}

	ResourceType Image::GetType()
	{
		return ResourceType::IMAGE;
	}

	void Image::Render(sf::RenderTarget& target)
	{
		target.draw(m_sprite);
	}

	void Image::SetPosition(const glm::vec3& position)
	{
		IRenderable::SetPosition(position);

		m_sprite.setPosition(sf::Vector2f(position.x, position.y));
	}
}