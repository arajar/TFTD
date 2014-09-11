#pragma once
#include <states/StateManager.h>

namespace core
{
	class FileSystem;
	class Engine
	{
	public:
		static sf::Font	DEBUG_FONT;
		static const int FPS;
		static const sf::Time TIME_PER_FRAME;

	public:
		explicit Engine(const std::string& name);
		virtual ~Engine();

	public:
		virtual bool Init();
		bool Run();

	public:
		void Resize(int width, int height);

	public:
		virtual void HandleEvents(core::WindowEvent event);
		virtual void Update(sf::Time elapsedTime);

	protected:
		virtual void ProcessEvents();

	protected:
		void BeginFrame();
		virtual void RenderFrame() = 0;
		void EndFrame();

	private:
		void Render();

	private:
		void UpdateStatistics(sf::Time elapsedTime);

	protected:
		const std::string		m_appName;

	protected:
		bool					m_running;

	protected:
		StateManager			m_stateMgr;

	protected:
		sf::RenderWindow*		m_window;
		sf::View				m_gameView;
		sf::RenderTexture		m_renderTarget;
		sf::Time				m_statisticsUpdateTime;

		size_t					m_statisticsNumFrames;

		sf::Clock				m_clock;
		sf::Time				m_timeSinceLastUpdate;
	
	protected:
		FileSystem m_fs;

	};
}