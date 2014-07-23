#include "pch.h"
#include "Image.h"

namespace core
{
	Image::Image(const std::string& name, SDL_Renderer* renderer)
		: IDrawable(renderer)
		, m_name(name)
		, m_width(0)
		, m_height(0)
		, m_texture(nullptr)
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

		m_width = surface->w;
		m_height = surface->h;

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

	vec2i Image::GetSize()
	{
		return std::make_pair(m_width, m_height);
	}

	SDL_Texture* Image::GetTexture()
	{
		return m_texture;
	}

	void Image::Render()
	{
		SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
	}
}