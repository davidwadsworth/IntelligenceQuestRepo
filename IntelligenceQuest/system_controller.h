#pragma once
#include "ECS.h"

namespace UpdateSystems
{
	class Controller : public System
	{
		int zaction = 0;
		int xaction = 0;
	public:
		Controller();
		~Controller();
		void update() override;
	};
}