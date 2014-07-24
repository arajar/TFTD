#include "pch.h"
#include "Image.h"

namespace core
{
	Image::Image(const std::string& name, SDL_Renderer* renderer)
		: IRenderable(renderer)
		, m_name(name)
	{
	}

	Image::~Image()
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}

	bool Image::Load()
	{
		SDL_Surface* surface = IMG_Load(m_name.c_str());

		if (surface == nullptr)
		{
			throw core::GameException(SDL_GetError());
			return nullptr;
		}

		m_size = std::make_pair(surface->w, surface->h);
		m_texture = SDL_CreateTextureFromSurface(ContentManager::GetInstance()->GetRenderer(), surface);
		if (m_texture == nullptr)
		{
			throw core::GameException(SDL_GetError());
			return nullptr;
		}

		SDL_FreeSurface(surface);

		return m_texture != nullptr;
	}

	ResourceType Image::GetType()
	{
		return ResourceType::IMAGE;
	}
}