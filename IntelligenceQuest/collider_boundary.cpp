#include "collider_boundary.h"

glm::vec2 Colliders::Boundary::find_perpendicular_line(Collider * col, glm::vec2 position)
{
	//TODO
	return glm::vec2();
}

glm::vec2 Colliders::Boundary::support(glm::vec2 direction)
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

Colliders::Boundary::Boundary(glm::vec2 * position, std::array<glm::vec2, MAX_BOUNDARY> vertices)
	: Collider(position, glm::abs(vertices[0] - vertices[1]) / 2.0f)
{}

Colliders::Boundary::~Boundary() = default;
