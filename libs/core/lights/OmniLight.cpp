#include "core.h"
#include "OmniLight.h"

namespace core
{
	//////////////////////////////////////////////////////////////////////////

	LightType OmniLight::GetType() const
	{
		return LightType::OMNI;
	}

	//////////////////////////////////////////////////////////////////////////

	void OmniLight::Generate(std::vector<Wall> walls)
	{
		m_shapes.clear();

		float buf = (glm::pi<float>() * 2) / static_cast<float>(m_quality);

		for (int i = 0; i < static_cast<int>(m_quality); i++)
		{
			const float ii = static_cast<float>(i);
			const float radius = static_cast<float>(m_radius);

			glm::vec2 p1(glm::vec2(radius * cos(ii * buf), radius * sin(ii * buf)));
			glm::vec2 p2(glm::vec2(radius * cos((ii + 1) * buf), radius * sin((ii + 1) * buf)));
			AddTriangle(p1, p2, 0, walls);
		}
	}

	//////////////////////////////////////////////////////////////////////////

}