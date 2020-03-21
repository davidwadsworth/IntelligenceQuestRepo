#pragma once
#include "ECS.h"

namespace UpdateSystems
{
	class Movement : public System
	{
	public:
		Movement();
		~Movement();
		void update() override;
	};

}
