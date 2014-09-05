#include "core.h"
#include "Util.h"

sf::Vector2f Util::Intersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
	sf::Vector2f i;

	if ((p2.x - p1.x) == 0 && (q2.x - q1.x) == 0)
	{
		i.x = 0, i.y = 0;
	}
	else if ((p2.x - p1.x) == 0)
	{
		i.x = p1.x;

		float c = (q2.y - q1.y) / (q2.x - q1.x);
		float d = q1.y - q1.x * c;

		i.y = c * i.x + d;
	}

	else if ((q2.x - q1.x) == 0)
	{
		i.x = q1.x;

		float a = (p2.y - p1.y) / (p2.x - p1.x);
		float b = p1.y - p1.x * a;

		i.y = a * i.x + b;
	}
	else
	{
		float a = (p2.y - p1.y) / (p2.x - p1.x);
		float b = p1.y - p1.x * a;

		float c = (q2.y - q1.y) / (q2.x - q1.x);
		float d = q1.y - q1.x * c;

		i.x = (d - b) / (a - c);
		i.y = a * i.x + b;
	}

	return i;
}

sf::Vector2f Util::Collision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
	sf::Vector2f i = Intersect(p1, p2, q1, q2);

	if (((i.x >= p1.x - 0.1 && i.x <= p2.x + 0.1)
		|| (i.x >= p2.x - 0.1 && i.x <= p1.x + 0.1))
		&& ((i.x >= q1.x - 0.1 && i.x <= q2.x + 0.1)
		|| (i.x >= q2.x - 0.1 && i.x <= q1.x + 0.1))
		&& ((i.y >= p1.y - 0.1 && i.y <= p2.y + 0.1)
		|| (i.y >= p2.y - 0.1 && i.y <= p1.y + 0.1))
		&& ((i.y >= q1.y - 0.1 && i.y <= q2.y + 0.1)
		|| (i.y >= q2.y - 0.1 && i.y <= q1.y + 0.1)))
	{
		return i;
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}