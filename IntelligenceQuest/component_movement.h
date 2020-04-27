#pragma once
#include "ECS.h"

namespace Components
{
	class Movement : public Component
	{
	public:
		glm::vec2 velocity;
		float speed;
		Movement(float speed);
		~Movement();
	};
}