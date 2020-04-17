#pragma once
#include <vec2.hpp>


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
		Transform(float x, float y, int h, int w, int sc);
	};
}
