#pragma once
#include "util/Timer.h"

namespace core
{
	class FileSystem;
	class Engine
	{
	public:
		static const int FPS;
		static const int SKIP_TICKS;

	public:
		Engine();
		virtual ~Engine();

	public:
		bool Init();
		bool Run();

	public:
		void Resize(int width, int height);

	public:
		virtual void HandleEvents(const SDL_Event& event) = 0;
		virtual void Update(Uint32 deltaTime);

	protected:
		void BeginFrame();
		virtual void RenderFrame() = 0;
		void EndFrame();

	private:
		void Render();

	protected:
		bool m_running;

	protected:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		FileSystem m_fs;

	private:
		util::Timer m_fpsTimer;
	};
}