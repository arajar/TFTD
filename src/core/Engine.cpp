#include "pch.h"
#include "Engine.h"
#include "ContentManager.h"

namespace core
{
	const int Engine::FPS = 60;
	const int Engine::SKIP_TICKS = 1000 / Engine::FPS;

	Engine::Engine()
		: m_window(nullptr)
		, m_renderer(nullptr)
		, m_fs("./Data")
	{
	}

	Engine::~Engine()
	{
		ContentManager::Destroy();

		TTF_Quit();
		IMG_Quit();

		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);

		SDL_Quit();
	}

	bool Engine::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			throw GameException(SDL_GetError());
			return false;
		}

		int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
		if (!IMG_Init(IMG_INIT_PNG) & imgFlags)
		{
			throw GameException(IMG_GetError());
			return false;
		}

		if (TTF_Init() != 0)
		{
			throw GameException(TTF_GetError());
			return false;
		}

		m_window = SDL_CreateWindow("TFTD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (m_window == nullptr)
		{
			throw GameException(SDL_GetError());
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_window == nullptr)
		{
			throw GameException(SDL_GetError());
		}

		// Singleton creation
		new ContentManager(m_renderer, "");

		m_fs.Init();
		m_fpsTimer.Start();

		return true;
	}

	void Engine::Resize(int width, int height)
	{
		if (width > 0 && height > 0)
		{
			SDL_SetWindowSize(m_window, width, height);
		}
	}

	bool Engine::Run()
	{
		SDL_Event event;

		m_fpsTimer.Start();
		Uint32 elapsedTime = m_fpsTimer.GetTicks();
		Uint32 prevFrametick = 0;
		while (m_running)
		{
			prevFrametick = elapsedTime;
			elapsedTime = m_fpsTimer.GetTicks();

			Uint32 deltaTime = elapsedTime - prevFrametick;

			m_fpsTimer.Start();
			while (SDL_PollEvent(&event))
			{
				HandleEvents(event);
			}

			Update(deltaTime);
			Render();

			if (m_fpsTimer.GetTicks() < Engine::SKIP_TICKS)
			{
				SDL_Delay(Engine::SKIP_TICKS - m_fpsTimer.GetTicks());
			}
		}

		return false;
	}

	void Engine::Update(Uint32 deltaTime)
	{
	}

	void Engine::Render()
	{
		BeginFrame();
		RenderFrame();
		EndFrame();
	}

	void Engine::BeginFrame()
	{
		SDL_RenderClear(m_renderer);
	}

	void Engine::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}
}