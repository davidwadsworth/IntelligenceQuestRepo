#include "stdafx.h"
#include "collider_circle.h"

Colliders::Circle::Circle(glm::vec2* position, glm::vec2 offset, float radius)
	: Collider(position, offset), radius_(radius)
{}

Colliders::Circle::Circle(glm::vec2* position, float radius)
	: Collider(position, glm::vec2(radius)), radius_(radius)
{}

Colliders::Circle::~Circle() = default;

glm::vec2 Colliders::Circle::support(glm::vec2 direction)
{
	return get_center() + radius_ * glm::normalize(direction);
}

glm::vec2 Colliders::Circle::find_perpendicular_line(Collider * col, glm::vec2 position)
{
	return glm::normalize(support(position - get_center()) - get_center());
}
