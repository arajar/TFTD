#include "pch.h"
#include "LightSystem.h"

#include "ecs/Light.h"
#include "lights/Light.h"

#include "Position.h"

namespace ecs
{
	//////////////////////////////////////////////////////////////////////////

	LightSystem::LightSystem(core::ecs::World& world)
		: System(world)
		, m_ambientColor(sf::Color::White)
		, m_lightSmooth(2)
	{
		m_priority = 2;
		m_type = core::ecs::SystemType::Render;

		m_blurEffect.loadFromFile("data/shaders/blur.frag", sf::Shader::Fragment);
		m_blurEffect.setParameter("texture", sf::Shader::CurrentTexture);

		m_renderImg.create(800, 600);
	}

	//////////////////////////////////////////////////////////////////////////

	LightSystem::~LightSystem()
	{
		//RemoveWalls();
	}

	//////////////////////////////////////////////////////////////////////////

	void LightSystem::Process(sf::RenderTarget& target)
	{
		Generate();
		sf::RenderStates r(sf::BlendMultiply);
		r.shader = &m_blurEffect;
		target.draw(sf::Sprite(m_renderImg.getTexture()), r);
	}

	//////////////////////////////////////////////////////////////////////////

	void LightSystem::Generate()
	{
		m_renderImg.clear(m_ambientColor);
		m_blurEffect.setParameter("offset", 0.005f * m_lightSmooth);

		for (auto e : m_world.GetEntitiesWith<ecs::Position, core::ecs::Light>())
		{
			auto& p = *m_world.GetComponent<ecs::Position>(e);
			core::ecs::Light& light = *m_world.GetComponent<core::ecs::Light>(e);

			if (light.light->IsActive())
			{
				light.light->SetPosition(sf::Vector2f(p.pos.x, p.pos.y));
				light.light->Generate(m_wall);
				light.light->Render(&m_renderImg);
			}
		}

		m_renderImg.display();
	}

	//////////////////////////////////////////////////////////////////////////

	void LightSystem::SetGlobalAmbientColor(const sf::Color& ambientColor)
	{
		m_ambientColor = std::move(ambientColor);
	}

	//////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

/*
WallEntity LightManager::AddWall(sf::Vector2f pt1, sf::Vector2f pt2)
{
for (int i = 0; i < (int)m_wall.size(); i++)
if ((pt1.y - pt2.y) / (pt1.x - pt2.y) == (m_wall[i].pt1.y - m_wall[i].pt2.y) / (m_wall[i].pt1.x - m_wall[i].pt2.y))
if (pt1 == m_wall[i].pt1 || pt2 == m_wall[i].pt1 || pt1 == m_wall[i].pt2 || pt2 == m_wall[i].pt2)
{
sf::Vector2f min = pt1, max = pt2;

if (pt2.x<min.x)
min.x = pt2.x;
if (pt1.x>max.x)
max.x = pt2.x;

if (m_wall[i].pt1.x<min.x)
min.x = m_wall[i].pt1.x;
if (m_wall[i].pt2.x<min.x)
min.x = m_wall[i].pt2.x;

if (m_wall[i].pt1.x>max.x)
max.x = m_wall[i].pt1.x;
if (m_wall[i].pt2.x>max.x)
max.x = m_wall[i].pt2.x;


if (pt2.y<min.y)
min.y = pt2.y;
if (pt1.y>max.y)
max.y = pt2.y;

if (m_wall[i].pt1.y<min.y)
min.y = m_wall[i].pt1.y;
if (m_wall[i].pt2.y<min.y)
min.y = m_wall[i].pt2.y;

if (m_wall[i].pt1.y>max.y)
max.y = m_wall[i].pt1.y;
if (m_wall[i].pt2.y>max.y)
max.y = m_wall[i].pt2.y;

m_wall[i].pt1 = min;
m_wall[i].pt2 = max;

return WallEntity(i);

}

m_wall.push_back(Wall(pt1, pt2));
return WallEntity(static_cast<int>(m_wall.size() - 1));
}
*/

//////////////////////////////////////////////////////////////////////////

/*
void LightManager::RemoveWall(WallEntity e)
{
m_wall.erase(m_wall.begin() + e.ID());
}

void LightManager::RemoveWalls()
{
m_wall.clear();
}
*/