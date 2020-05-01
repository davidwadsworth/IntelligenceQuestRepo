#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "texture_manager.h"
#include "collider.h"

namespace Components
{
	class Collision : public Component
	{
		Collider* collider_;
		QuadTree* collision_tree_;
	public:
		std::string tag;

		explicit Collision(std::string t, QuadTree* collision_tree, Collider* collider);
		~Collision();
		
		Collider* get_collider();
		QuadTree* get_collision_tree();
	};
}
