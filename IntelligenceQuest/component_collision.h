#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "texture_manager.h"

namespace Components
{

	class Collision : public Component
	{
	public:
		std::string tag;

		Collision(std::string t);
		Collision(std::string t, int xpos, int ypos, int size);
		
		~Collision();

	};
}
