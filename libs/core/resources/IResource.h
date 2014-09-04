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
	IRenderable() {}

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
	virtual void Write(const std::string& text, const glm::ivec2& pos) = 0;
};