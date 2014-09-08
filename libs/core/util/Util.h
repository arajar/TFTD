#pragma once

class Util
{
public:
	static const glm::vec2 Intersect(const glm::vec2&  p1, const glm::vec2&  p2, const glm::vec2&  q1, const glm::vec2&  q2);
	static const glm::vec2 Collision(const glm::vec2&  p1, const glm::vec2&  p2, const glm::vec2&  q1, const glm::vec2&  q2);
};