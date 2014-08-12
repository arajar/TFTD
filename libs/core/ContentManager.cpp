#include "core.h"
#include "ContentManager.h"

#include "resources\Image.h"
#include "resources\Font.h"
#include "resources\Sound.h"

namespace core
{
	ContentManager::ContentManager(SDL_Renderer* renderer, const std::string& pathToContent)
		: m_renderer(renderer)
		, m_pathToContent(pathToContent)
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

	SDL_Renderer* ContentManager::GetRenderer() const
	{
		return m_renderer;
	}
}