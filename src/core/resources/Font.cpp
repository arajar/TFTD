#include "pch.h"
#include "Font.h"

namespace core
{
	Font::Font(const std::string& fontName)
		: IDrawable(nullptr)
		, m_fontName(fontName)
		, m_font(nullptr)
		, m_texture(nullptr)
		, m_fontSize(25)
	{

	}

	Font::~Font()
	{

	}

	bool Font::Load()
	{
		try
		{
			m_font = TTF_OpenFont(m_fontName.c_str(), m_fontSize);
		}
		catch (const core::GameException& ex)
		{
			std::cout << ex.what() << std::endl;
			return false;
		}

		return true;
	}

	ResourceType Font::GetType()
	{
		return ResourceType::FONT;
	}

	vec2i Font::GetSize()
	{
		return m_textureSize;
	}

	SDL_Texture* Font::GetTexture()
	{
		return m_texture;
	}

	void Font::Write(SDL_Renderer* renderer, const std::string& text, const vec2i& pos, const SDL_Color& color)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(m_font, text.c_str(), color);
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}

		m_texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_QueryTexture(m_texture, NULL, NULL, &m_textureSize.first, &m_textureSize.second);
		m_rect = { pos.first, pos.second, m_textureSize.first, m_textureSize.second };
	}

	SDL_Rect Font::GetRect() const
	{
		return m_rect;
	}
}