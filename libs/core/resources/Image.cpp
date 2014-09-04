#include "core.h"
#include "Image.h"

namespace core
{
	Image::Image(const std::string& name)
		: m_name(name)
	{
	}

	Image::~Image()
	{
	}

	bool Image::Load()
	{
		/*
		SDL_Surface* surface = IMG_Load(m_name.c_str());

		if (surface == nullptr)
		{
			throw core::GameException(SDL_GetError());
			return nullptr;
		}

		m_size = glm::ivec2(surface->w, surface->h);
		m_texture = SDL_CreateTextureFromSurface(ContentManager::GetInstance()->GetRenderer(), surface);
		if (m_texture == nullptr)
		{
			throw core::GameException(SDL_GetError());
			return nullptr;
		}

		SDL_FreeSurface(surface);

		return m_texture != nullptr;
		*/
		return true;
	}

	ResourceType Image::GetType()
	{
		return ResourceType::IMAGE;
	}
}