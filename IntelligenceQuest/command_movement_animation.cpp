#include "stdafx.h"
#include "command_movement_animation.h"

Commands::MovementAnimation::MovementAnimation(Components::Physics *physics, Components::FrameAnimation * frame_animation)
	: physics_(physics), frame_animation_(frame_animation)
{}

Commands::MovementAnimation::~MovementAnimation() = default;

void Commands::MovementAnimation::execute()
{
	frame_animation_->is_animated = true;
	const auto direction = physics_->direction;

	if (direction.x > 0)
	{
		if (direction.y < 0)
			frame_animation_->play("walk up right");
		else if (direction.y > 0)
			frame_animation_->play("walk down right");
		else
			frame_animation_->play("walk right");
	}
	else if (direction.x < 0)
	{
		if (direction.y < 0)
			frame_animation_->play("walk up left");
		else if (direction.y > 0)
			frame_animation_->play("walk down left");
		else
			frame_animation_->play("walk left");
	}
	else
	{
		if (direction.y < 0)
			frame_animation_->play("walk up");
		else if (direction.y > 0)
			frame_animation_->play("walk down");
		else
			frame_animation_->is_animated = false;
	}
}

