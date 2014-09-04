#pragma once

typedef std::function<float(float)> InterpolationFunction;

namespace core
{
	namespace util
	{
		template<typename InterpType>
		class Tweener
		{
		public:
			Tweener()
				: m_interpFunction(nullptr)
				, m_initialValue()
				, m_currentValue()
				, m_targetValue()
				, m_delayTime(0)
				, m_accumTime(0)
				, m_updating(true)
			{
			}

			Tweener(InterpolationFunction interpFunction, InterpType initialValue, InterpType targetValue, uint32_t delay)
				: m_interpFunction(interpFunction)
				, m_initialValue(initialValue)
				, m_currentValue(initialValue)
				, m_targetValue(targetValue)
				, m_delayTime(delay)
				, m_accumTime(0)
				, m_updating(m_initialValue != m_targetValue)
			{
			}

			virtual ~Tweener() {}

		public:
			bool Update(sf::Time deltaTime)
			{
				if (m_interpFunction)
				{
					if (m_updating)
					{
						m_accumTime += deltaTime;
						if (m_accumTime >= m_delayTime)
						{
							m_currentValue = m_targetValue;
							m_updating = false;
						}
						else
						{
							float t = static_cast<float>(m_accumTime) / static_cast<float>(m_delayTime);
							t = m_interpFunction(t);

							m_currentValue = m_initialValue + (m_targetValue - m_initialValue) * t;
						}
						return true;
					}
					return false;
				}
				return false;
			}


		public:
			InterpType GetValue() const
			{
				return m_currentValue;
			}

			uint32_t GetDelay() const
			{
				return m_delayTime;
			}

			InterpType GetInitialValue() const
			{
				return m_initialValue;
			}

			InterpType GetTargetValue() const
			{
				return m_targetValue;
			}

			bool HasFinished() const
			{
				return !m_updating;
			}

		public:
			void SetEaseFunction(InterpolationFunction func)
			{
				m_interpFunction = func;
			}

			void Reset(InterpType initial, InterpType target)
			{
				m_initialValue = initial;
				m_currentValue = initial;
				m_targetValue = target;
			}

			void SetDelay(uint32_t delay)
			{
				m_delayTime = delay;
				m_accumTime = 0;
			}

			void SetTargetValue(InterpType value)
			{
				m_targetValue = value;
				m_initialValue = m_currentValue;
				m_updating = m_targetValue != m_currentValue;
			}

		private:
			InterpolationFunction m_interpFunction;

		private:
			InterpType m_initialValue;
			InterpType m_currentValue;
			InterpType m_targetValue;
			uint32_t m_delayTime;
			uint32_t m_accumTime;
			bool m_updating;
		};
	}
}
