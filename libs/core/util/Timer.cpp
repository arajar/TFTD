#include "core.h"
#include "Timer.h"

namespace core
{
	namespace util
	{
		Timer::Timer()
			: m_startTicks(0)
			, m_pausedTicks(0)
			, m_status(Status::STOPPED)
		{
		}

		Timer::~Timer()
		{
		}

		void Timer::Start()
		{
			m_status = Status::STARTED;

			m_startTicks = SDL_GetTicks();
			m_pausedTicks = 0;
		}

		void Timer::Stop()
		{
			m_status = Status::STOPPED;

			m_startTicks = 0;
			m_pausedTicks = 0;
		}

		void Timer::Pause()
		{
			if (m_status == Status::STARTED)
			{
				m_status = Status::PAUSED;

				m_pausedTicks = SDL_GetTicks() - m_startTicks;
				m_startTicks = 0;
			}
		}

		void Timer::Resume()
		{
			if (m_status == Status::PAUSED)
			{
				m_status = Status::STARTED;

				m_startTicks = SDL_GetTicks() - m_pausedTicks;
				m_pausedTicks = 0;
			}
		}

		Uint32 Timer::GetTicks() const
		{
			Uint32 time = 0;

			if (m_status == Status::STARTED)
			{
				time = SDL_GetTicks() - m_startTicks;
			}
			else if (m_status == Status::PAUSED)
			{
				time = m_pausedTicks;
			}

			return time;
		}

		Timer::Status Timer::GetStatus() const
		{
			return m_status;
		}
	}
}