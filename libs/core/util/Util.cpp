#include "core.h"
#include "Util.h"

const glm::vec2 Util::Intersect(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2)
{
	glm::vec2 i;

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

const glm::vec2 Util::Collision(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2)
{
	glm::vec2 i = Intersect(p1, p2, q1, q2);

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
		return glm::vec2(0, 0);
	}
}