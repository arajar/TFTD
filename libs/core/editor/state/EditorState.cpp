#include "core.h"
#include "EditorState.h"
#include "Map.h"
#include "Tileset.h"
#include <editor/Node.h>

namespace editor
{
	EditorState::EditorState(core::ecs::World& world, const std::string& tilesetName)
		: State(world)
		, m_tilesetName(tilesetName)
		, m_tileSet(nullptr)
		, m_map(nullptr)
		, m_selectedNode(nullptr)
		, m_selectedTile(0)
		, m_mousePressed(false)
	{
	}

	void EditorState::Start()
	{
		m_debugText.setFont(core::Engine::DEBUG_FONT);

		m_tileSet = new editor::Tileset(m_tilesetName);
		m_tileSet->Init();

		m_map = new editor::Map();

		m_selectedNode = new editor::Node(glm::vec2(0.f, 0.f), 1, m_tileSet->GetTiles().front());
	}

	void EditorState::Resume()
	{
	}

	void EditorState::Suspend()
	{
	}

	void EditorState::End()
	{
	}

	void EditorState::HandleEvents(const core::WindowEvent windowEvent)
	{
		State::HandleEvents(windowEvent);

		switch (windowEvent.event.type)
		{
			case sf::Event::MouseWheelMoved: 
			{
				int next = windowEvent.event.mouseWheel.delta > 0 ? 1 : -1;

				m_selectedTile = (m_selectedTile + next) % (m_tileSet->GetTiles().size()-1);
				m_selectedNode->SetSurface(m_tileSet->GetTiles()[m_selectedTile]);

				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (!m_mousePressed)
				{
					m_mousePressed = true;
					m_map->CloneNode(m_selectedNode);
				}
				break;
			}
			case sf::Event::MouseButtonReleased: 
			{
				m_mousePressed = false;
				break; 
			}
			default: break;
		}

		int x = sf::Mouse::getPosition(*windowEvent.window).x;
		int y = sf::Mouse::getPosition(*windowEvent.window).y;
		x -= m_selectedNode->GetSurface()->image->GetSize().x / 2;
		y -= m_selectedNode->GetSurface()->image->GetSize().y / 2;
		m_selectedNode->SetPos(glm::vec2(x, y));

	}

	void EditorState::Update(sf::Time deltaTime)
	{
		State::Update(deltaTime);
	}

	void EditorState::Render(sf::RenderTarget& target)
	{
		State::Render(target);
		for (auto& node : m_map->GetNodes())
		{
			node->Render(target);
			node->RenderBounds(target);
		}

		m_selectedNode->Render(target);
	}

	void EditorState::RenderDebug(sf::RenderTarget& target)
	{
		m_debugText.setString("Editor");
		target.draw(m_debugText);
	}
}