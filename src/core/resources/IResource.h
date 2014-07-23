#pragma once

enum class ResourceType
{
	IMAGE,
	FONT,
	MUSIC,
	SOUND,
};

class IResource
{
public:
	virtual bool Load() = 0;
	virtual ResourceType GetType() = 0;
};

class IDrawable
{
public:
	IDrawable(SDL_Renderer* renderer) : m_renderer(renderer) {}

	virtual std::pair<int, int> GetSize() = 0;
	virtual SDL_Texture* GetTexture() = 0;

	virtual void Render() = 0;

protected:
	SDL_Renderer* m_renderer;
};

class IText
{
public:
	virtual void Write(SDL_Renderer* renderer, const std::string& text, const std::pair<int, int>& pos, const SDL_Color& color) = 0;
	virtual SDL_Rect GetRect() const = 0;
};