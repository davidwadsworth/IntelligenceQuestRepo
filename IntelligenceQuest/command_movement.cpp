#include "stdafx.h"
#include "command_movement.h"

Commands::Movement::Movement(Components::Movement* movement, Components::Transform* transform)
	: transform_(transform), movement_(movement)
{}

Commands::Movement::~Movement() = default;

void Commands::Movement::execute()
{
	transform_->position.x += movement_->velocity.x * movement_->speed;
	transform_->position.y += movement_->velocity.y * movement_->speed;
}

