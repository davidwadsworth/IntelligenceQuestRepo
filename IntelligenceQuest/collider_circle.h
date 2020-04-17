#pragma once
#include "collider.h"

namespace Colliders
{
	class Circle : public Collider
	{
		float radius_;
		glm::vec2 support(glm::vec2 direction) override;
		glm::vec2 find_perpendicular_line(Collider * col, glm::vec2 prev_position) override;
	public:
		Circle(glm::vec2* position, glm::vec2 offset, float radius);
		~Circle();
	};
}
