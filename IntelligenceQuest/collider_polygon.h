#pragma once
#include "collider.h"
#include <glm.hpp>
#include <vector>

namespace Colliders
{
	class Polygon : public Collider
	{
		float shortest_magnitude_, shortest_distance_;

		std::vector<glm::vec2> vertices_;
		glm::vec2 support(glm::vec2 direction) override;
		
		glm::vec2 find_center(std::vector<glm::vec2> vertices);

		void find_closest_distance(float& closest_distance, glm::vec2& closest_vertex, glm::vec2 p1, glm::vec2 p2, glm::vec2 direction, int index);

	public:
		Polygon(glm::vec2* position, std::vector<glm::vec2> vertices);
		Polygon(glm::vec2* position, glm::vec2 offset, std::vector<glm::vec2> vertices);
		~Polygon();

		glm::vec2 find_perpendicular_line(Collider * col, glm::vec2 position) override;
	};
}
