#pragma once

namespace editor
{
	class Node;
	struct TileSurface;

	typedef std::vector<Node*> NodeList;

	class Map
	{
		ID(Map);

	public:
		Map();
		virtual ~Map();

	public:
		Node* CreateNode(glm::vec2 pos, int layer, TileSurface* surface);
		void DeleteNode(Node* node);
		Node* CloneNode(Node* node);

		NodeList GetNodes() const;

	private:
		NodeList m_nodes;

		int m_nodeIds;		
	};
}