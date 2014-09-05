#include "core.h"
#include "Engine.h"
#include "ContentManager.h"

namespace core
{
	const int Engine::FPS = 60;
	const sf::Time Engine::TIME_PER_FRAME = sf::seconds(1.f / Engine::FPS);

	Engine::Engine()
		: m_window(nullptr)
		, m_fs("./Data")
	{
	}

	Engine::~Engine()
	{
		ContentManager::Destroy();
	}

	bool Engine::Init()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(640, 480), "tftd", sf::Style::Close | sf::Style::Resize);
		if (m_window == nullptr)
		{
			throw GameException("Could not create window.");
		}

		m_renderTarget.create(640, 480);
		m_window->setFramerateLimit(60);
		
		m_fs.Init();

		m_font.loadFromFile(m_fs["sansation.ttf"]);
		m_statisticsText.setFont(m_font);
		m_statisticsText.setPosition(5.f, 5.f);
		m_statisticsText.setCharacterSize(14);
		
		// Singleton creation
		new ContentManager(m_fs);

		return true;
	}

	void Engine::Resize(int width, int height)
	{
		if (width > 0 && height > 0)
		{
			m_renderTarget.create(width, height);
			m_window->create(sf::VideoMode(width, height), "tftd", sf::Style::Close | sf::Style::Resize);
		}
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
	}

	void Engine::ProcessEvents()
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				HandleEvents(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				HandleEvents(event.key.code, false);
				break;

			case sf::Event::Resized:
				Resize(m_window->getSize().x, m_window->getSize().y);
				break;

			case sf::Event::Closed:
				m_window->close();
				break;
			}
		}
	}

	void Engine::Render()
	{
		BeginFrame();
		RenderFrame();
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
		m_window->draw(m_statisticsText);

		m_window->display();
	}

	void Engine::UpdateStatistics(sf::Time elapsedTime)
	{
		m_statisticsUpdateTime += elapsedTime;
		m_statisticsNumFrames += 1;

		if (m_statisticsUpdateTime >= sf::seconds(1.0f))
		{
			m_statisticsText.setString(
				"Frames / Second = " + std::to_string(m_statisticsNumFrames) + "\n" +
				"Time / Update = " + std::to_string(m_statisticsUpdateTime.asMicroseconds() / m_statisticsNumFrames) + "us");

			m_statisticsText.setPosition(sf::Vector2f(5.f, 5.f));
			m_statisticsUpdateTime -= sf::seconds(1.0f);
			m_statisticsNumFrames = 0;
		}
	}
}