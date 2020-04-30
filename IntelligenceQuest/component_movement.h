#pragma once
#include "ECS.h"

namespace Components
{
	class Movement : public Component
	{
	public:
		glm::vec2 direction;
		float speed;
		Movement(float speed);
		~Movement();
	};
}