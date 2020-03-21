#pragma once

#include <string>
#include "InputContext.h"
#include "ECS.h"
#include "game.h"
#include "Context.h"
#include "Inputs.h"
#include <SDL.h>
#include <cmath>



namespace Components
{
	class Controller : public Component
	{
	public:
		Controller();
		~Controller();
	};
}

