#pragma once
#include "collider.h"
#include <glm.hpp>
#include <vector>

namespace Colliders
{
	class Polygon : public Collider
	{
		std::vector<glm::vec2> vertices_;
		glm::vec2 support(glm::vec2 direction) override;
		
		glm::vec2 find_center(std::vector<glm::vec2> vertices);

	public:
		Polygon(glm::vec2* position, std::vector<glm::vec2> vertices);
		~Polygon();

		glm::vec2 find_perpendicular_line(Collider * col, glm::vec2 position) override;
	};
}
