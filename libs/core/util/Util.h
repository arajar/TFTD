#pragma once

class Util
{
public:
	static sf::Vector2f Intersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);
	static sf::Vector2f Collision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);
};