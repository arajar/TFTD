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
	virtual ~ITransform() {}

	virtual void SetPosition(const glm::vec3& position)
	{
		m_position = position;
	}

	virtual const glm::vec3& GetPosition() const
	{
		return m_position;
	}

protected:
	glm::vec3 m_position;
};

class IRenderable : public ITransform
{
public:
	IRenderable() {}

	virtual void Render(sf::RenderTarget& target) = 0;

	virtual const glm::ivec2& GetSize() const
	{
		return m_size;
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
	glm::ivec2 m_size;
	int m_layer;
};

class IText
{
public:
	virtual ~IText() {}

	virtual void Write(const std::string& text, const glm::ivec2& pos) = 0;
};