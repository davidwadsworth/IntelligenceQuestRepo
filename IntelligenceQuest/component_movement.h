#pragma once
#include "ECS.h"

namespace Components
{
	class Movement : public Component
	{
	public:
		glm::vec2 force;
		Movement();
		~Movement();
	};
}