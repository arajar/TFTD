#include "core.h"
#include "ContentManager.h"

#include "resources\Image.h"
#include "resources\Sound.h"

namespace core
{
	ContentManager::ContentManager(FileSystem& fs)
		: m_fs(fs)
	{
	}

	ContentManager::~ContentManager()
	{
		try
		{
			Unload();
		}
		catch (const GameException& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void ContentManager::Unload()
	{
		for (auto res : m_resources)
		{
			delete res.second;
			res.second = nullptr;
		}

		m_resources.clear();
	}
}