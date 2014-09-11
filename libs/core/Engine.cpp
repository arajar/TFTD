#include "core.h"
#include "Engine.h"
#include "ContentManager.h"

#include <editor/resources/Tileset.h>
#include <editor/state/EditorState.h>

namespace core
{
	const int Engine::FPS = 60;
	const sf::Time Engine::TIME_PER_FRAME = sf::seconds(1.f / FPS);
	sf::Font Engine::DEBUG_FONT = sf::Font();

	Engine::Engine(const std::string& name)
		: m_appName(name)
		, m_window(nullptr)
		, m_fs("./Data")
	{
	}

	Engine::~Engine()
	{
		ContentManager::Destroy();
	}

	bool Engine::Init()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(640, 480), m_appName, sf::Style::Close | sf::Style::Resize);
		if (m_window == nullptr)
		{
			throw GameException("Could not create window.");
		}

		m_renderTarget.create(640, 480);
		m_window->setFramerateLimit(60);

		sf::Vector2f size = sf::Vector2f(m_window->getSize());
		m_gameView.setSize(size);
		m_gameView.setCenter(size*0.5f);
		//m_window->setView(m_gameView);

		m_fs.Init();

		DEBUG_FONT.loadFromFile(m_fs["sansation.ttf"]);

		// Singleton creation
		new ContentManager(m_fs);

		return true;
	}

	void Engine::Resize(int width, int height)
	{
		if (width > 0 && height > 0)
		{
			TODO("Figure a better method to handle window resizing, as this method destroys and recreates the window");
			m_renderTarget.create(width, height);
			m_window->create(sf::VideoMode(width, height), m_appName, sf::Style::Close | sf::Style::Resize);
			m_gameView.setSize(width, height);
		}
	}

	void Engine::HandleEvents(core::WindowEvent event)
	{
		m_stateMgr.HandleEvents(event);
	}

	bool Engine::Run()
	{
		while (m_window->isOpen())
		{
			sf::Time elapsedTime = m_clock.restart();
			m_timeSinceLastUpdate += elapsedTime;
			while (m_timeSinceLastUpdate > TIME_PER_FRAME)
			{
				m_timeSinceLastUpdate -= TIME_PER_FRAME;

				ProcessEvents();
				Update(TIME_PER_FRAME);
			}

			UpdateStatistics(elapsedTime);
			Render();
		}

		return false;
	}

	void Engine::Update(sf::Time deltaTime)
	{
		m_stateMgr.Update(deltaTime);
	}

	void Engine::ProcessEvents()
	{
		core::WindowEvent coreEvent(m_window, m_gameView, m_renderTarget);
		
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			coreEvent.event = event;
			HandleEvents(coreEvent);
			switch (event.type)
			{
			case sf::Event::Resized:
				Resize(event.size.width, event.size.height);
				break;

			case sf::Event::Closed:
				m_window->close();
				break;
			default: break;
			}
		}
	}

	void Engine::Render()
	{
		//m_window->setView(m_gameView);
		m_renderTarget.setView(m_gameView);
		BeginFrame();
		RenderFrame();
		m_stateMgr.Render(m_renderTarget);
		EndFrame();
	}

	void Engine::BeginFrame()
	{
		m_window->clear(sf::Color(50, 50, 50));
		m_renderTarget.clear(sf::Color(50, 50, 50));
	}

	void Engine::EndFrame()
	{
		m_renderTarget.display();

		sf::Sprite s(m_renderTarget.getTexture());
		m_window->draw(s);

		m_window->display();
	}

	void Engine::UpdateStatistics(sf::Time deltaTime)
	{
		m_statisticsUpdateTime += deltaTime;
		m_statisticsNumFrames += 1;

		if (m_statisticsUpdateTime >= sf::seconds(1.0f))
		{
			std::string info = m_appName + " - Frames / Second = " + std::to_string(m_statisticsNumFrames) + "\n" +
				"Time / Update = " + std::to_string(m_statisticsUpdateTime.asMicroseconds() / m_statisticsNumFrames) + "us";

			m_window->setTitle(info);

			m_statisticsUpdateTime -= sf::seconds(1.0f);
			m_statisticsNumFrames = 0;
		}
	}
}