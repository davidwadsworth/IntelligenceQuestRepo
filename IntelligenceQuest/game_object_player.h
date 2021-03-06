#pragma once
#include "game_object.h"
#include "component_animation.h"
#include "component_physics.h"
#include "component_movement.h"

namespace  GameObjects
{
	class Player : public GameObject
	{
		glm::vec2 position_;
		int player_width_, player_height_;
		float scale_, speed_;
		QuadTree* collision_tree_;
	public:
		Components::Transform* transform;
		Components::Render* render;
		Components::Collision* collision;
		Components::FrameAnimation* frame_animation;
		Components::Movement* movement;
		Components::Physics* physics;
		Entity* entity;
		Player(std::string tex, QuadTree* collision_tree, glm::vec2 position, int player_width, int player_height, float scale, float speed);
		~Player();
	};
}
