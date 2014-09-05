#pragma once

//////////////////////////////////////////////////////////////////////////

#include "ecs/System.h"

//////////////////////////////////////////////////////////////////////////

namespace ecs
{
	class LightSystem : public core::ecs::System
	{
	public:
		LightSystem(core::ecs::World& world);
		~LightSystem();

	public:
		void Process(sf::RenderTarget& target);

	public:
		//void AddWall(sf::Vector2f pt1, sf::Vector2f pt2);
		//void RemoveWall(WallEntity);
		//void RemoveWalls();

	public:
		void Generate();

	public:
		void SetGlobalAmbientColor(const sf::Color& ambientColor);

	protected:
		std::vector<struct Wall> m_wall;

	private:
		sf::Shader m_blurEffect;
		sf::RenderTexture m_renderImg;

		sf::Color m_ambientColor;
		int m_lightSmooth;
	};
}

//////////////////////////////////////////////////////////////////////////
