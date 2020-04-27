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

glm::vec2 Colliders::Polygon::find_center(std::vector<glm::vec2> vertices)
{
	glm::vec2 center = glm::vec2();
	for (auto v : vertices)
		center += v;

	return center / static_cast<float>(vertices.size());
}

Colliders::Polygon::Polygon(glm::vec2 * position,std::vector<glm::vec2> vertices)
	: Collider(position, find_center(vertices)), vertices_(vertices) 
{
	vertices_.shrink_to_fit();

	if (vertices_.size() < 3)
		SDL_Log("Invalid Polygon");
}

Colliders::Polygon::~Polygon() = default;

/***
* assuming this polygon is made of at least three points
* assuming this polygon is not concave
*
* this function finds the closest edge (A) and the neighboring points (B) and (C) based on colliding object position before collision occured (O)
* B = previous vertex, C = next vertex
* because the polygon is concave it cannot collide with two edges
*
* if the center is along A->B return ⊥AB
* if the center is along C->A return ⊥CA
* else the center is exactly between the two edges return O-A and if multiplied by 
*
* O
*
*    A----------B
*     \
*      \
*       \
*        C
*
* eg. O is closer to a point on line AB than CA return ⊥AB
*/


glm::vec2 Colliders::Polygon::find_perpendicular_line(Collider * col, glm::vec2 position)
{
	auto closest_distance = -FLT_MAX;
	auto A = glm::vec2(); // closest vertex
	auto closest_index = 0;

	auto center = this->get_center();

	auto direction = position - center;

	for (auto i = 0; i < vertices_.size(); i++)
	{
		auto distance = glm::dot(vertices_[i] + center, direction);
		if (distance > closest_distance)
		{
			closest_distance = distance;
			A = vertices_[i];
			closest_index = i;
		}
	}

	auto B = vertices_[(closest_index + 1) < vertices_.size() ? closest_index + 1 : 0];
	auto C = vertices_[(closest_index - 1) >= 0 ? closest_index - 1 : vertices_.size() - 1];

	auto slope = A.y / A.x;

	auto fO = direction.x * slope - direction.y;
	auto fC = C.x * slope - C.y;
	auto fB = B.x * slope - B.y;

	auto CA_perpendicular = (fO < fC && fO > 0.0f) || (fO > fC && fO < 0.0f);
	auto AB_perpendicular = (fO < fB && fO > 0.0f) || (fO > fB && fO < 0.0f);

	if (CA_perpendicular)
	{
		auto CA = glm::normalize(A - C);
		return glm::vec2(CA.y, -CA.x); // return the perpendicular vector ⊥CA
	}
	if (AB_perpendicular)
	{
		auto AB = glm::normalize(B - A);
		return glm::vec2(AB.y, -AB.x); // return the perpendicular vector ⊥AB
	}

	return glm::vec2(A.x / abs(A.x), A.y / abs(A.y)); // return the edge vector 
}
