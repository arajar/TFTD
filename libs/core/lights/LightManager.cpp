#include "core.h"
#include "LightManager.h"
#include "Light.h"

//////////////////////////////////////////////////////////////////////////

LightManager::LightManager()
	: m_ambientColor(sf::Color::White)
	, m_lightSmooth(2)
{
	m_blurEffect.loadFromFile("data/shaders/blur.frag", sf::Shader::Fragment);
	m_blurEffect.setParameter("texture", sf::Shader::CurrentTexture);

	m_renderImg.create(800, 600);
}

//////////////////////////////////////////////////////////////////////////

LightManager::~LightManager()
{
	RemoveLights();
	//RemoveWalls();
}

//////////////////////////////////////////////////////////////////////////

void LightManager::Render(sf::RenderWindow* window)
{
	sf::RenderStates r(sf::BlendMultiply);
	r.shader = &m_blurEffect;
	window->draw(sf::Sprite(m_renderImg.getTexture()), r);
}

//////////////////////////////////////////////////////////////////////////

void LightManager::AddLight(ILight* light)
{
	m_lights.push_back(light);
}

//////////////////////////////////////////////////////////////////////////

void LightManager::AddLight(std::nullptr_t light)
{
	// ASSERT OR SOMETHING
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

void LightManager::RemoveLight(ILight* light)
{
	auto it = std::find(m_lights.begin(), m_lights.end(), light);
	if (it != m_lights.end())
	{
		m_lights.erase(it);

		light->SetActive(false);
		delete light;
	}
}

//////////////////////////////////////////////////////////////////////////

void LightManager::RemoveLights()
{
	for (auto light : m_lights)
	{
		delete light;
	}

	m_lights.clear();
}

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

//////////////////////////////////////////////////////////////////////////

void LightManager::Generate()
{
	m_renderImg.clear(m_ambientColor);
	m_blurEffect.setParameter("offset", 0.005f * m_lightSmooth);

	std::vector<ILight*>::iterator it;

	for (auto light : m_lights)
	{
		if (light->IsActive())
		{
			light->Generate(m_wall);
			light->Render(&m_renderImg);
		}
	}

	m_renderImg.display();
}

//////////////////////////////////////////////////////////////////////////

void LightManager::Generate(ILight* light)
{
	light->Generate(m_wall);
}

//////////////////////////////////////////////////////////////////////////

void LightManager::Generate(std::nullptr_t light)
{
	// ASSERT OR SOMETHING
}

//////////////////////////////////////////////////////////////////////////

void LightManager::SetGlobalAmbientColor(const sf::Color& ambientColor)
{
	m_ambientColor = std::move(ambientColor);
}

//////////////////////////////////////////////////////////////////////////
