#pragma once
#include <vec2.hpp>
#include "ecs.h"

namespace Components
{
	class Transform : public Component
	{
	public:
		glm::vec2 prev_position;
		glm::vec2 position;

		int height = 32;
		int width = 32;
		int scale = 1;

		Transform();
		explicit Transform(int sc);
		Transform(float x, float y);
		Transform(glm::vec2 position, int h, int w);
		Transform(float x, float y, int h, int w, int sc);
	};
}
