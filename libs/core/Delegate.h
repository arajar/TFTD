#pragma once

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename ... Args>
class Delegate
{
public:
	template<typename U>
	Delegate& operator+=(const U& func)
	{
		m_funcs.push_back(std::function<T(Args...)>(func));
		return *this;
	}

	std::vector<T> operator() (Args...params)
	{
		std::vector<T> ret;
		for (auto f : m_funcs)
		{
			ret.push_back(f(params...));
		}
		
		return ret;
	}
	
private:
	std::vector<std::function<T(Args...)>> m_funcs;

};

///////////////////////////////////////////////////////////////////////////////

template <typename ... Args>
class Delegate<void, Args...>
{
public:
	template<typename U>
	Delegate& operator+=(const U& func)
	{
		m_funcs.push_back(std::function<void(Args...)>(func));
		return *this;
	}

	void operator() (Args...params)
	{
		for (auto f : m_funcs)
		{
			f(params...);
		}
	}

private:
	std::vector<std::function<void(Args...)>> m_funcs;

};

///////////////////////////////////////////////////////////////////////////////
