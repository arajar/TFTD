#pragma once

namespace core
{
	namespace util
	{
		class Timer
		{
		public:
			enum class Status
			{
				STARTED,
				PAUSED,
				STOPPED,
			};

		public:
			Timer();
			virtual ~Timer();

		public:
			void Start();
			void Stop();
			void Pause();
			void Resume();

		public:
			Uint32 GetTicks() const;

			Status GetStatus() const;

		private:
			Uint32 m_startTicks;
			Uint32 m_pausedTicks;

			Status m_status;
		};
	}
}