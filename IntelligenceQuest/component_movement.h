#pragma once
#include "ECS.h"

namespace Components
{
	class Movement : public Component
	{
	public:
		float speed;
		glm::vec2 velocity;
		Movement(float speed);
		~Movement();
	};
}