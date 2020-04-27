#pragma once
#include <geometric.hpp>
#include <vec3.hpp>
#include <cmath>
#include <vec2.hpp>
#include <array>
#include "component_transform.h"

/*
 Kenton Hamaluik wrote all this. Thank you Kenton 
*/

constexpr std::size_t MAX_SIMPLEX = 3;
constexpr std::size_t MAX_INTERSECTING = 32;

class Collider
{
	std::array<glm::vec2, MAX_SIMPLEX> vertices_;
	virtual glm::vec2 support(glm::vec2 direction) = 0;

	struct Edge
	{
		float distance;
		glm::vec2 normal;
		int index;
	};

	Edge find_closest_edge(bool clockwise);

	glm::vec2* position_;
	glm::vec2 offset_;
public:
	Collider(glm::vec2* position, glm::vec2 offset);
	~Collider();

	glm::vec2 triple_product(glm::vec2 a, glm::vec2 b, glm::vec2 c);
	glm::vec2 get_center();
	glm::vec2 get_offset() const;
	bool collide(Collider * col);
	glm::vec2 intersecting_vector(Collider * col);
	virtual glm::vec2 find_perpendicular_line(Collider * col, glm::vec2 position) = 0;
};
