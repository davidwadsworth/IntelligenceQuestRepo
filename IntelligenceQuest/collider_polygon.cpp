#include "stdafx.h"
#include "collider_polygon.h"

glm::vec2 Colliders::Polygon::support(glm::vec2 direction)
{
	auto furthest_distance = std::numeric_limits<float>::lowest();
	auto furthest_vertex = glm::vec2();

	for (auto v : vertices_)
	{
		auto distance = glm::dot(v + get_center(), direction);
		if (distance > furthest_distance)
		{
			furthest_distance = distance;
			furthest_vertex = v + get_center();
		}
	}

	return furthest_vertex;
}

Colliders::Polygon::Polygon(glm::vec2 * position, glm::vec2 offset, std::vector<glm::vec2> vertices)
	: Collider(position, offset), vertices_(vertices) 
{
	vertices_.shrink_to_fit();
}

Colliders::Polygon::~Polygon() = default;

glm::vec2 Colliders::Polygon::find_perpendicular_line(Collider * col, glm::vec2 position)
{
	auto starting_point = support(get_center() - position);

	return glm::vec2();
}
