#pragma once
#include <geometric.hpp>
#include <vec3.hpp>
#include <cmath>
#include <vec2.hpp>
#include <array>
#include "component_transform.h"
#include "quad_tree.h"

/*
 Kenton Hamaluik wrote all this. Thank you Kenton 

 After testing Kenton Hamaluiks code I have realized he is not as brilliant as I first thought,
	he still saved several hours of my time though and I thank him greatly.
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

	glm::vec2* position_;
	glm::vec2 offset_;
public:
	Collider(glm::vec2 *position);
	Collider(glm::vec2* position, glm::vec2 offset);
	~Collider();

	glm::vec2 triple_product(glm::vec2 a, glm::vec2 b, glm::vec2 c);
	glm::vec2 get_center();
	glm::vec2 get_position();
	glm::vec2 get_offset() const;
	
	void set_offset(glm::vec2 offset);

	bool collide(Collider * col);
	virtual glm::vec2 find_perpendicular_line(Collider * col, glm::vec2 position) = 0;
};
