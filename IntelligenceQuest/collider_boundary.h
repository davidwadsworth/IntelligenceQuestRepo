#pragma once
#include "collider.h"

constexpr std::size_t MAX_BOUNDARY = 2;

namespace Colliders
{
	class Boundary : public Collider
	{
		std::array<glm::vec2, MAX_BOUNDARY> vertices_;
		glm::vec2 find_perpendicular_line(Collider* col, glm::vec2 position) override;
		glm::vec2 support(glm::vec2 direction) override;
	public:
		Boundary(glm::vec2* position, std::array<glm::vec2, MAX_BOUNDARY> vertices);
		~Boundary();
	};

}

