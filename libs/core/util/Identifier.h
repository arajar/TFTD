#pragma once


///////////////////////////////////////////////////////////////////////////////

template<class C, typename T = int32_t>
struct Identifier
{
	inline Identifier() : m_value() {}
	inline explicit Identifier(const T& i) : m_value(i) {}
	inline Identifier(const Identifier<C, T>& i) : m_value(i.m_value) {}

	inline const T& value() const
	{
		return m_value;
	}

	inline bool operator==(const Identifier<C, T>& id) const { return m_value == id.m_value; }
	inline bool operator!=(const Identifier<C, T>& id) const { return m_value != id.m_value; }
	inline T operator++() { return m_value++; }

private:
	T m_value;
};

///////////////////////////////////////////////////////////////////////////////

namespace std
{
	template <class C, typename T>
	struct less<Identifier<C, T> > : binary_function <Identifier<C, T>, Identifier<C, T>, bool>
	{
		bool operator() (const Identifier<C, T>& x, const Identifier<C, T>& y) const
		{
			return x.value()<y.value();
		} 
	};
};


///////////////////////////////////////////////////////////////////////////////

#define ID(x) public: typedef Identifier<x> Id; protected: Id m_id;

///////////////////////////////////////////////////////////////////////////////
