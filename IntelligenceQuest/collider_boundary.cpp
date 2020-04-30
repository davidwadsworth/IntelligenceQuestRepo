#include "stdafx.h"
#include "collider_boundary.h"

glm::vec2 Colliders::Boundary::find_perpendicular_line(Collider * col, glm::vec2 position)
{
	auto line = glm::normalize(vertices_[1] - vertices_[0]);
	return glm::vec2(line.x, -line.y);
}

glm::vec2 Colliders::Boundary::support(glm::vec2 direction)
{
	auto p1 = vertices_[0] + get_position();
	auto p2 = vertices_[1] + get_position();

	auto p1_distance = glm::dot(p1, direction);
	auto p2_distance = glm::dot(p2, direction);

	if (p1_distance > p2_distance)
		return p1;
	else
		return p2;
}

Colliders::Boundary::Boundary(glm::vec2 * position, std::array<glm::vec2, MAX_BOUNDARY> vertices)
	: Collider(position, glm::abs(vertices[1] - vertices[0]) / 2.0f), vertices_(vertices)
{}

Colliders::Boundary::~Boundary() = default;
