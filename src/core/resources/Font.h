#pragma once

namespace core
{
	class Font : public IResource, public IRenderable, public IText
	{
	public:
		Font(const std::string& fontName);
		virtual ~Font();

	public: // IResource interface
		virtual bool Load() override;
		virtual ResourceType GetType() override;

	public: // IText interface
		virtual void Write(SDL_Renderer* renderer, const std::string& text, const glm::ivec2& pos, const SDL_Color& color) override;
		virtual SDL_Rect GetRect() const override;

	private:
		const std::string m_fontName;
		const int m_fontSize;
	
		TTF_Font* m_font;
		SDL_Rect m_rect;
	};
}