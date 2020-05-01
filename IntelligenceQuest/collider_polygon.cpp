#include "stdafx.h"
#include "collider_polygon.h"

Colliders::Polygon::Polygon(glm::vec2 * position, std::vector<glm::vec2> vertices)
	: Collider(position), vertices_(vertices), shortest_magnitude_()
{
	auto line = vertices_[1] - vertices_[0];
	shortest_magnitude_ = line.x * line.x + line.y * line.y;
	shortest_distance_ = glm::sqrt(shortest_magnitude_);

	set_offset(find_center(vertices_));
	vertices_.shrink_to_fit();
}

Colliders::Polygon::Polygon(glm::vec2 * position, glm::vec2 offset, std::vector<glm::vec2> vertices)
	: Collider(position, offset), vertices_(vertices), shortest_magnitude_()
{
	vertices_.shrink_to_fit();
}

Colliders::Polygon::~Polygon() = default;

glm::vec2 Colliders::Polygon::support(glm::vec2 direction)
{
	auto furthest_distance = std::numeric_limits<float>::lowest();
	auto furthest_vertex = glm::vec2();

	for (auto v : vertices_)
	{
		auto distance = glm::dot(v + get_position(), direction);
		if (distance > furthest_distance)
		{
			furthest_distance = distance;
			furthest_vertex = v + get_position();
		}
	}

	return furthest_vertex;
}

glm::vec2 Colliders::Polygon::find_center(std::vector<glm::vec2> vertices)
{
	glm::vec2 center = glm::vec2();
	for (auto v : vertices)
		center += v;

	return center / static_cast<float>(vertices.size());
}


/**
* DO NOT LOAD IN A POLYGON WITH ITS SHORTEST LENGTH MORE THAN TWICE AS SHORT AS ITS LONGEST LENGTH
*/

void Colliders::Polygon::find_closest_distance(float& closest_distance, glm::vec2& closest_vertex, glm::vec2 p1, glm::vec2 p2, glm::vec2 direction, int index)
{
	auto p = p2 - p1;
	auto p_magnitude = p.x * p.x + p.y * p.y;

	if (p_magnitude > shortest_magnitude_ + 0.5f || p_magnitude < shortest_magnitude_ - 0.5f)
	{
		auto du = shortest_distance_ * glm::normalize(p);
		find_closest_distance(closest_distance, closest_vertex, p1, p1 + du, direction, vertices_.size()); // check if closest distance then exit
		find_closest_distance(closest_distance, closest_vertex, p2 - du, p2, direction, index);
		return;
	}

	auto distance = glm::dot(p2, direction) + glm::dot(p1, direction);

	if (distance > closest_distance)
	{
		closest_distance = distance;
		closest_vertex = p;
	}

	if (index >= vertices_.size())
		return;

	p1 = vertices_[index];
	p2 = vertices_[0];

	if (++index < vertices_.size())
		p2 = vertices_[index];

	find_closest_distance(closest_distance, closest_vertex, p1, p2, direction, index);
}

/***
* normalizes the polygon into same lengthed vertexes and from those created vertexes checks  
*/


glm::vec2 Colliders::Polygon::find_perpendicular_line(Collider * col, glm::vec2 position)
{
	auto closest_distance = -FLT_MAX;
	auto closest_vertex = glm::vec2(); 
	
	auto direction = position - this->get_center();

	find_closest_distance(closest_distance, closest_vertex, vertices_[0], vertices_[1], direction, 1);

	closest_vertex = glm::normalize(closest_vertex);

	return glm::vec2(closest_vertex.y, -closest_vertex.x);
}
