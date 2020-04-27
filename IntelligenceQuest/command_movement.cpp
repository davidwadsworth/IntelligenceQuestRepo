#include "stdafx.h"
#include "command_movement.h"

Commands::Movement::Movement(Components::Movement* movement, Components::Transform* transform)
	: transform_(transform), movement_(movement)
{}

Commands::Movement::~Movement() = default;

void Commands::Movement::execute()
{
	transform_->prev_position = transform_->position;
	transform_->position.x += movement_->velocity.x * movement_->speed * Game::delta_time;
	transform_->position.y += movement_->velocity.y * movement_->speed * Game::delta_time;
}

