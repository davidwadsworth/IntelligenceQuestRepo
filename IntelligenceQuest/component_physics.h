#pragma once
#include "ecs.h"
#include <vec2.hpp>

namespace Components
{
	class Physics : public Component
	{
	public:
		Physics(int mass);
		~Physics();

		int mass;
		glm::vec2 force, prev_force, direction;
	};
}
