#include "core.h"
#include "Map.h"

#include "Node.h"
#include "Tileset.h"

namespace editor
{
	Map::Map()
		: m_nodeIds(0)
	{
	}

	Map::~Map()
	{
		for (auto n : m_nodes)
		{
			if (n)
			{
				delete n;
			}
		}
	}

	Node* Map::CreateNode(glm::vec2 pos, int layer, TileSurface* surface)
	{
		auto node = new Node(pos, layer, surface);
		node->m_id = Node::Id(m_nodeIds++);
		m_nodes.push_back(node);

		return node;
	}

	void Map::DeleteNode(Node* node)
	{
		auto n = std::find(m_nodes.begin(), m_nodes.end(), node);
		if (n != m_nodes.end())
		{
			m_nodes.erase(n);
			delete (*n);
		}
	}

	Node* Map::CloneNode(Node* node)
	{
		auto newNode = new Node(node->GetPos(), node->GetLayer(), node->GetSurface());
		newNode->m_id = Node::Id(m_nodeIds++);
		m_nodes.push_back(newNode);

		return newNode;
	}

	NodeList Map::GetNodes() const
	{
		return m_nodes;
	}
}
