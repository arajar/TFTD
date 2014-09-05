#pragma once
#include "LightBase.h"

namespace core
{
	//////////////////////////////////////////////////////////////////////////

	class OmniLight : public LightBase
	{
	public:
		virtual LightType GetType() const override;

	public:
		virtual void Generate(std::vector<Wall> walls) override;
	};

	//////////////////////////////////////////////////////////////////////////
}