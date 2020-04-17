#include "stdafx.h"
#include "command_movement.h"

Commands::Movement::Movement(Components::Movement* movement, Components::Transform* transform)
	: transform_(transform), movement_(movement)
{}

Commands::Movement::~Movement() = default;

void Commands::Movement::execute()
{
	transform_->prev_position = transform_->position;
	transform_->position.x += (movement_->force.x) * Game::delta_time;
	transform_->position.y += (movement_->force.y) * Game::delta_time;
	movement_->force = { 0, 0 };
}

