#include "stdafx.h"
#include "command_movement_animation.h"

Commands::MovementAnimation::MovementAnimation(Components::Movement *movement, Components::FrameAnimation * frame_animation)
	: movement_(movement), frame_animation_(frame_animation)
{}

Commands::MovementAnimation::~MovementAnimation() = default;

void Commands::MovementAnimation::execute()
{
	frame_animation_->is_animated = true;
	const auto vel = movement_->velocity;

	if (vel.x > 0)
	{
		if (vel.y < 0)
			frame_animation_->play("walk up right");
		else if (vel.y > 0)
			frame_animation_->play("walk down right");
		else
			frame_animation_->play("walk right");
	}
	else if (vel.x < 0)
	{
		if (vel.y < 0)
			frame_animation_->play("walk up left");
		else if (vel.y > 0)
			frame_animation_->play("walk down left");
		else
			frame_animation_->play("walk left");
	}
	else
	{
		if (vel.y < 0)
			frame_animation_->play("walk up");
		else if (vel.y > 0)
			frame_animation_->play("walk down");
		else
			frame_animation_->is_animated = false;
	}
}

