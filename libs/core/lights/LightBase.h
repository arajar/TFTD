#pragma once
#include "Light.h"

namespace core
{
	//////////////////////////////////////////////////////////////////////////

	class LightBase : public ILight
	{
	public:
		LightBase();
		virtual ~LightBase();

	public:
		virtual void Render(sf::RenderTarget* rt) override;

	public:
		virtual void SetPosition(const glm::vec2& pos) override;
		virtual void SetColor(const sf::Color& color) override;
		virtual void SetQuality(LightQuality quality) override;
		virtual void SetIntensity(float intensity) override;
		virtual void SetRadius(float radius) override;

		virtual const glm::vec2& GetPosition() const override;
		virtual const sf::Color& GetColor() const override;
		virtual LightQuality GetQuality() const override;
		virtual float GetIntensity() const override;
		virtual float GetRadius() const override;

		virtual void SetActive(bool active) override;
		virtual bool IsActive() override;

	protected:
		virtual void AddTriangle(glm::vec2 point1, glm::vec2 point2, int minWall, std::vector<Wall>& walls);

	protected:
		glm::vec2						m_position;
		sf::Color						m_color;
		LightQuality					m_quality;

		float							m_intensity;
		float							m_radius;

		bool							m_active;

		std::vector<sf::VertexArray>	m_shapes;
	};

	//////////////////////////////////////////////////////////////////////////

}