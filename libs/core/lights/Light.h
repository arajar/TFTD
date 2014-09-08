#pragma once

//////////////////////////////////////////////////////////////////////////
struct Wall
{
	Wall(sf::Vector2f p1, sf::Vector2f p2)
	{
		pt1 = p1;
		pt2 = p2;
	}

	sf::Vector2f pt1;
	sf::Vector2f pt2;
};

//////////////////////////////////////////////////////////////////////////

struct WallEntity
{
	WallEntity(int id)
	{
		m_ID = id;
	}

	int GetID() { return m_ID; }

private:

	int m_ID;
};

//////////////////////////////////////////////////////////////////////////

enum class LightType
{
	OMNI,
	SPOT,
};

//////////////////////////////////////////////////////////////////////////

enum class LightQuality
{
	ULTRA = 18,
	GOOD = 14,
	FAIR = 10,
	LOW = 6,
	LOWEST = 4,
};

//////////////////////////////////////////////////////////////////////////

namespace core
{
	// Interface for Lights
	class ILight
	{
	public:
		virtual ~ILight() {}

	public:
		virtual void Render(sf::RenderTarget* rt) = 0;

	public:
		virtual void SetPosition(const glm::vec2& pos) = 0;
		virtual void SetColor(const sf::Color& color) = 0;
		virtual void SetQuality(LightQuality quality) = 0;
		virtual void SetIntensity(float intensity) = 0;
		virtual void SetRadius(float radius) = 0;

		virtual const glm::vec2& GetPosition() const = 0;
		virtual const sf::Color& GetColor() const = 0;
		virtual LightQuality GetQuality() const = 0;
		virtual float GetIntensity() const = 0;
		virtual float GetRadius() const = 0;

		virtual LightType GetType() const = 0;

		virtual void SetActive(bool active) = 0;
		virtual bool IsActive() = 0;

	public:
		virtual void Generate(std::vector<Wall> walls) = 0;

	};

	//////////////////////////////////////////////////////////////////////////
}