#pragma once
#include "Light.h"

//////////////////////////////////////////////////////////////////////////

class LightBase : public ILight
{
public:
	LightBase();
	virtual ~LightBase();

public:
	virtual void Render(sf::RenderTarget* rt) override;

public:
	virtual void SetPosition(const sf::Vector2f& pos) override;
	virtual void SetColor(const sf::Color& color) override;
	virtual void SetQuality(LightQuality quality) override;
	virtual void SetIntensity(float intensity) override;
	virtual void SetRadius(float radius) override;

	virtual const sf::Vector2f& GetPosition() const override;
	virtual const sf::Color& GetColor() const override;
	virtual LightQuality GetQuality() const override;
	virtual float GetIntensity() const override;
	virtual float GetRadius() const override;

	virtual void SetActive(bool active) override;
	virtual bool IsActive() override;

protected:
	virtual void AddTriangle(sf::Vector2f point1, sf::Vector2f point2, int minWall, std::vector<Wall>& walls);

protected:
	sf::Vector2f					m_position;
	sf::Color						m_color;
	LightQuality					m_quality;

	float							m_intensity;
	float							m_radius;

	bool							m_active;

	std::vector<sf::VertexArray>	m_shapes;
};

//////////////////////////////////////////////////////////////////////////
