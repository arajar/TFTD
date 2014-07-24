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

class ITransform
{
public:
	virtual void SetPosition(const vec2i& position)
	{
		m_position = position;
	}

	virtual const vec2i& GetPosition() const
	{
		return m_position;
	}

protected:
	vec2i m_position;
};

class IRenderable : public ITransform
{
public:
	IRenderable(SDL_Renderer* renderer) : m_renderer(renderer), m_texture(nullptr) {}

	virtual const vec2i& GetSize() const
	{
		return m_size;
	}

	virtual SDL_Texture* GetTexture()
	{
		return m_texture;
	}

	virtual void Render()
	{
		const int x = m_position.first;
		const int y = m_position.second;
		const int w = m_size.first;
		const int h = m_size.second;

		SDL_Rect dst = { x, y, w, h };

		SDL_RenderCopy(m_renderer, m_texture, NULL, &dst);
	}

	void SetLayer(int layer)
	{
		m_layer = layer;
	}

	int GetLayer() const
	{
		return m_layer;
	}

protected:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	vec2i m_size;
	int m_layer;
};

class IText
{
public:
	virtual void Write(SDL_Renderer* renderer, const std::string& text, const std::pair<int, int>& pos, const SDL_Color& color) = 0;
	virtual SDL_Rect GetRect() const = 0;
};