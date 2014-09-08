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

		float buf = (glm::pi<float>() * 2) / (float)m_quality;

		for (int i = 0; i < (int)m_quality; i++)
		{
			glm::vec2 p1(glm::vec2((float)((float)m_radius * cos((float)i * buf)), (float)((float)m_radius * sin((float)i * buf))));
			glm::vec2 p2(glm::vec2((float)((float)m_radius * cos((float)(i + 1) * buf)), (float)((float)m_radius * sin((float)(i + 1) * buf))));
			AddTriangle(p1, p2, 0, walls);
		}
	}

	//////////////////////////////////////////////////////////////////////////

}