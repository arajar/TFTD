#include "core.h"
#include "SpotLight.h"

//////////////////////////////////////////////////////////////////////////

SpotLight::SpotLight()
	: LightBase()
	, m_angle(0.f)
	, m_openingAngle(0.f)
{
}

//////////////////////////////////////////////////////////////////////////

void SpotLight::Generate(std::vector<Wall> wall)
{
	m_shapes.clear();

	float angle = m_angle * glm::pi<float>() / 180.f;
	float o_angle = m_openingAngle * glm::pi<float>() / 180.f;

	AddTriangle(sf::Vector2f((m_radius*cos(angle + o_angle * 0.5f))
		, (m_radius*sin(angle + o_angle * 0.5f))),
		sf::Vector2f((m_radius*cos(angle - o_angle * 0.5f))
		, (m_radius*sin(angle - o_angle * 0.5f))), 0, wall);
}

//////////////////////////////////////////////////////////////////////////

void SpotLight::SetAngle(float angle)
{
	m_angle = angle;
}

//////////////////////////////////////////////////////////////////////////

void SpotLight::SetOpeningAngle(float angle)
{
	m_openingAngle = angle;
}

//////////////////////////////////////////////////////////////////////////

LightType SpotLight::GetType() const
{
	return LightType::SPOT;
}

//////////////////////////////////////////////////////////////////////////

