#include "core.h"
#include "Node.h"

#include "Tileset.h"

namespace editor
{
	Node::Node(glm::vec2 pos, int layer, TileSurface* surf)
		: m_pos(pos)
		, m_layer(layer)
		, m_surface(surf)
	{
	}

	Node::~Node()
	{
		if (m_surface)
		{
			delete m_surface;
			m_surface = nullptr;
		}
	}

	void Node::Render(sf::RenderTarget& target)
	{
		m_surface->image->SetPosition(glm::vec3(m_pos.x, m_pos.y, 0.f));
		m_surface->image->Render(target);
	}

	void Node::RenderBounds(sf::RenderTarget& target)
	{
		sf::RectangleShape shape(sf::Vector2f(m_surface->image->GetSize().x, m_surface->image->GetSize().y));
		shape.setPosition(sf::Vector2f(m_pos.x, m_pos.y));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);

		target.draw(shape);
	}

	void Node::SetPos(glm::vec2 const& pos)
	{
		m_pos = pos;
	}

	void Node::SetLayer(int layer)
	{
		m_layer = layer;
	}

	void Node::SetSurface(TileSurface* surface)
	{
		m_surface = surface;
	}

	glm::vec2 Node::GetPos() const
	{
		return m_pos;
	}

	int Node::GetLayer() const
	{
		return m_layer;
	}

	TileSurface* Node::GetSurface() const
	{
		return m_surface;
	}
}
