#pragma once

//////////////////////////////////////////////////////////////////////////

enum class LightType
{
	OMNI,
	SPOT,
};

//////////////////////////////////////////////////////////////////////////

enum class LightQuality
{
	ULTRA = 64,
	GOOD = 14,
	FAIR = 10,
	LOW = 6,
	LOWEST = 4,
};

//////////////////////////////////////////////////////////////////////////

namespace core
{
	struct Wall
	{
		glm::vec2 pt1;
		glm::vec2 pt2;
	};


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