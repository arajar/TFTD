#pragma once
#include <states/State.h>
#include <editor/Map.h>

///////////////////////////////////////////////////////////////////////////////

namespace editor
{
	class Tileset;

	class EditorState : public State
	{
	public:
		EditorState(core::ecs::World& world, const std::string& tilesetName);
		virtual ~EditorState() {}

	public:
		virtual void Start() override;
		virtual void Resume() override;
		virtual void Suspend() override;
		virtual void End() override;
		virtual void HandleEvents(core::WindowEvent event) override;
		virtual void Update(sf::Time deltaTime) override;
		virtual void Render(sf::RenderTarget& target) override;
		virtual void RenderDebug(sf::RenderTarget& target) override;

	private:
		const std::string	m_tilesetName;
		editor::Tileset*	m_tileSet;
		editor::Map*		m_map;
		
	private:
		editor::Node*		m_selectedNode;
		int					m_selectedTile;
		bool				m_mousePressed;

		sf::Vector2i		m_mouseCurrentPos;
		sf::Vector2i		m_mouseClickedPos;
		float zoomLevel = 1.0;
	};
}

//////////////////////////////////////////////////////////////////////////

