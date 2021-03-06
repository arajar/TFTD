#include "core.h"
#include "LightBase.h"

namespace core
{
	//////////////////////////////////////////////////////////////////////////

	LightBase::LightBase()
		: m_position(0.f, 0.f)
		, m_color(sf::Color::White)
		, m_quality(LightQuality::FAIR)
		, m_intensity(0.f)
		, m_radius(0.f)
		, m_active(true)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	LightBase::~LightBase()
	{
		m_shapes.clear();
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::Render(sf::RenderTarget* rt)
	{
		for (auto& shape : m_shapes)
		{
			rt->draw(shape, sf::BlendAdd);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::SetPosition(const glm::vec2& position)
	{
		m_position = position;
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::SetColor(const sf::Color& color)
	{
		m_color = color;
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::SetQuality(LightQuality quality)
	{
		m_quality = quality;
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::SetIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::SetRadius(float radius)
	{
		m_radius = radius;
	}

	//////////////////////////////////////////////////////////////////////////

	const glm::vec2& LightBase::GetPosition() const
	{
		return m_position;
	}

	//////////////////////////////////////////////////////////////////////////

	const sf::Color& LightBase::GetColor() const
	{
		return m_color;
	}

	//////////////////////////////////////////////////////////////////////////

	LightQuality LightBase::GetQuality() const
	{
		return m_quality;
	}

	//////////////////////////////////////////////////////////////////////////

	float LightBase::GetIntensity() const
	{
		return m_intensity;
	}

	//////////////////////////////////////////////////////////////////////////

	float LightBase::GetRadius() const
	{
		return m_radius;
	}

	//////////////////////////////////////////////////////////////////////////

	void LightBase::SetActive(bool active)
	{
		m_active = active;
	}

	//////////////////////////////////////////////////////////////////////////

	bool LightBase::IsActive()
	{
		return m_active;
	}

	//////////////////////////////////////////////////////////////////////////


	void LightBase::AddTriangle(glm::vec2 pt1, glm::vec2 pt2, int minimum_wall, std::vector<Wall> &m_wall)
	{
		int w = minimum_wall;

		for (std::vector<Wall>::iterator it = m_wall.begin() + minimum_wall; it != m_wall.end(); ++it, ++w)
		{
			// l1 and l2 are the relative positions from the wall to the light
			glm::vec2 l1(it->pt1.x - m_position.x, it->pt1.y - m_position.y);
			glm::vec2 l2(it->pt2.x - m_position.x, it->pt2.y - m_position.y);

			if (l1.x * l1.x + l1.y * l1.y < m_radius * m_radius)
			{
				glm::vec2 i = Util::Intersect(pt1, pt2, glm::vec2(0, 0), l1);

				if (pt1 != i && pt2 != i)
				{
					if ((pt1.x >= i.x && pt2.x <= i.x) || (pt1.x <= i.x && pt2.x >= i.x))
					{
						if ((pt1.y >= i.y && pt2.y <= i.y) || (pt1.y <= i.y && pt2.y >= i.y))
						{
							if ((l1.y >= 0 && i.y >= 0) || (l1.y <= 0 && i.y <= 0))
							{
								if ((l1.x >= 0 && i.x >= 0) || (l1.x <= 0 && i.x <= 0))
								{
									AddTriangle(i, pt2, w, m_wall), pt2 = i;
								}
							}
						}
					}
				}
			}

			if (l2.x * l2.x + l2.y * l2.y < m_radius * m_radius)
			{
				glm::vec2 i = Util::Intersect(pt1, pt2, glm::vec2(0, 0), l2);

				if (pt1 != i && pt2 != i)
				{
					if ((pt1.x >= i.x && pt2.x <= i.x) || (pt1.x <= i.x && pt2.x >= i.x))
					{
						if ((pt1.y >= i.y && pt2.y <= i.y) || (pt1.y <= i.y && pt2.y >= i.y))
						{
							if ((l2.y >= 0 && i.y >= 0) || (l2.y <= 0 && i.y <= 0))
							{
								if ((l2.x >= 0 && i.x >= 0) || (l2.x <= 0 && i.x <= 0))
								{
									AddTriangle(pt1, i, w, m_wall), pt1 = i;
								}
							}
						}
					}
				}
			}

			glm::vec2 m = Util::Collision(l1, l2, glm::vec2(0.f, 0.f), pt1);
			glm::vec2 n = Util::Collision(l1, l2, glm::vec2(0.f, 0.f), pt2);
			glm::vec2 o = Util::Collision(l1, l2, pt1, pt2);

			if ((m.x != 0 || m.y != 0) && (n.x != 0 || n.y != 0))
			{
				pt1 = m, pt2 = n;
			}
			else
			{
				if ((m.x != 0 || m.y != 0) && (o.x != 0 || o.y != 0))
				{
					AddTriangle(m, o, w, m_wall), pt1 = o;
				}

				if ((n.x != 0 || n.y != 0) && (o.x != 0 || o.y != 0))
				{
					AddTriangle(o, n, w, m_wall), pt2 = o;
				}
			}
		}

		float intensity = 0.f;

		m_shapes.push_back(sf::VertexArray());
		m_shapes.back().setPrimitiveType(sf::Triangles);

		m_shapes.back().append(sf::Vertex(sf::Vector2f(m_position.x, m_position.y), sf::Color(
			static_cast<int>(m_intensity * m_color.r / 255),
			static_cast<int>(m_intensity * m_color.g / 255),
			static_cast<int>(m_intensity * m_color.b / 255))));

		intensity = m_intensity - sqrt(pt1.x * pt1.x + pt1.y * pt1.y) * m_intensity / m_radius;
		m_shapes.back().append(sf::Vertex(sf::Vector2f(m_position.x + pt1.x, m_position.y + pt1.y), sf::Color(
			static_cast<int>(intensity * m_color.r / 255),
			static_cast<int>(intensity * m_color.g / 255),
			static_cast<int>(intensity * m_color.b / 255))));

		intensity = m_intensity - sqrt(pt2.x * pt2.x + pt2.y * pt2.y) * m_intensity / m_radius;
		m_shapes.back().append(sf::Vertex(sf::Vector2f(m_position.x + pt2.x, m_position.y + pt2.y), sf::Color(
			static_cast<int>(intensity * m_color.r / 255),
			static_cast<int>(intensity * m_color.g / 255),
			static_cast<int>(intensity * m_color.b / 255))));
	}

	//////////////////////////////////////////////////////////////////////////

}