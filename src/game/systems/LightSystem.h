#pragma once

//////////////////////////////////////////////////////////////////////////

#include "ecs/System.h"

//////////////////////////////////////////////////////////////////////////

namespace ecs
{
	class LightSystem : public core::ecs::System
	{
		NAME(LightSystem)

	public:
		explicit LightSystem(core::ecs::World& world);
		~LightSystem();

	public:
		void Process(sf::RenderTarget& target) override;

	public:
		void Generate();

	public:
		void SetGlobalAmbientColor(const sf::Color& ambientColor);

	private:
		sf::Shader m_blurEffect;
		sf::RenderTexture m_renderImg;

		sf::Color m_ambientColor;
		int m_lightSmooth;
	};
}

//////////////////////////////////////////////////////////////////////////
