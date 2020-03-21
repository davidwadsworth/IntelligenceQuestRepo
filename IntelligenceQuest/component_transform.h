#pragma once
#include <vec2.hpp>


namespace Components
{
	class Transform : public Component
	{

	public:
		//TODO remove velocity from this monstrocity
		glm::vec2 position;
		glm::vec2 velocity = glm::vec2(0.0f,0.0f);

		int height = 32;
		int width = 32;
		int scale = 1;

		int speed = 3;

		Transform();
		explicit Transform(int sc);
		Transform(float x, float y);
		Transform(float x, float y, int h, int w, int sc);
	};
}
