#pragma once

//////////////////////////////////////////////////////////////////////////

class ILight;

//////////////////////////////////////////////////////////////////////////

class LightManager : public Singleton<LightManager>
{
public:
	LightManager();
	~LightManager();

public:
	void Render(sf::RenderWindow* window);

public:
	void AddLight(ILight* light);
	void AddLight(std::nullptr_t light);
	//void AddWall(sf::Vector2f pt1, sf::Vector2f pt2);

	void RemoveLight(ILight* light);
	void RemoveLights();
	//void RemoveWall(WallEntity);
	//void RemoveWalls();

public:
	void Generate();
	void Generate(ILight* light);
	void Generate(std::nullptr_t light);

public:
	void SetGlobalAmbientColor(const sf::Color& ambientColor);

protected:
	std::vector<struct Wall> m_wall;
	std::vector<ILight*> m_lights;

private:
	sf::Shader m_blurEffect;
	sf::RenderTexture m_renderImg;

	sf::Color m_ambientColor;
	int m_lightSmooth;
};

//////////////////////////////////////////////////////////////////////////
