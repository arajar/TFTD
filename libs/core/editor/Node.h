#pragma once

namespace editor
{
	struct TileSurface;

	class Node
	{
		friend class Map;
		ID(Node);

	public:
		Node(glm::vec2 pos, int layer, TileSurface* surf);
		virtual ~Node();

	public:
		void			Render(sf::RenderTarget& target);
		void			RenderBounds(sf::RenderTarget& target);

	public:
		void			SetPos(const glm::vec2& pos);
		void			SetLayer(int layer);
		void			SetSurface(TileSurface* surface);

		glm::vec2		GetPos() const;
		int				GetLayer() const;
		TileSurface*	GetSurface() const;

	private:
		glm::vec2		m_pos;
		int				m_layer;
		TileSurface*	m_surface;
	};
}