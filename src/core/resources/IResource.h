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
	virtual void SetPosition(const glm::ivec2& position)
	{
		m_position = position;
	}

	virtual const glm::ivec2& GetPosition() const
	{
		return m_position;
	}

protected:
	glm::ivec2 m_position;
};

class IRenderable : public ITransform
{
public:
	IRenderable(SDL_Renderer* renderer) : m_renderer(renderer), m_texture(nullptr) {}

	virtual const glm::ivec2& GetSize() const
	{
		return m_size;
	}

	virtual SDL_Texture* GetTexture()
	{
		return m_texture;
	}

	virtual void Render()
	{
		const int x = m_position.x;
		const int y = m_position.y;
		const int w = m_size.x;
		const int h = m_size.y;

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
	glm::ivec2 m_size;
	int m_layer;
};

class IText
{
public:
	virtual void Write(SDL_Renderer* renderer, const std::string& text, const glm::ivec2& pos, const SDL_Color& color) = 0;
	virtual SDL_Rect GetRect() const = 0;
};