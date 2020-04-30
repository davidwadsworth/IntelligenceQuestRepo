#include "stdafx.h"
#include "command_force.h"

Commands::Force::Force(Components::Physics* physics, Components::Transform* transform)
	: transform_(transform), physics_(physics)
{}

Commands::Force::~Force() = default;

void Commands::Force::execute()
{
	transform_->prev_position = transform_->position;
	transform_->position += physics_->force * physics_->direction * Game::delta_time;
	physics_->prev_force = physics_->force;
	physics_->force = glm::vec2();
}

