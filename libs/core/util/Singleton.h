#pragma once

///////////////////////////////////////////////////////////////////////////////
// Singleton implementation

template <class T>
class Singleton
{
public:
	static T* GetInstance();
	static bool Exists();
	static void Destroy();

protected:
	Singleton();
	virtual ~Singleton();

	Singleton(const Singleton&) = delete; // Disallow copying
	Singleton& operator=(const Singleton&) = delete; // Disallow copying

private:
	static std::unique_ptr<T> s_instance;
};

//////////////////////////////////////////////////////////////////////////

template <class T>
std::unique_ptr<T> Singleton<T>::s_instance = nullptr;

//////////////////////////////////////////////////////////////////////////

template <class T>
T* Singleton<T>::GetInstance()
{
	// doesn't create the instance automatically
	return s_instance.get();
}

//////////////////////////////////////////////////////////////////////////

template <class T>
bool Singleton<T>::Exists()
{
	return s_instance.get() != nullptr;
}

//////////////////////////////////////////////////////////////////////////

template <class T>
void Singleton<T>::Destroy()
{
	s_instance.release();
	s_instance = nullptr;
}

//////////////////////////////////////////////////////////////////////////

template <class T>
Singleton<T>::Singleton()
{
	s_instance.reset(static_cast<T*>(this));
}

//////////////////////////////////////////////////////////////////////////

template <class T>
Singleton<T>::~Singleton()
{
	s_instance = nullptr;
}

///////////////////////////////////////////////////////////////////////////////