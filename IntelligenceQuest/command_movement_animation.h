#pragma once
#include "component_movement.h"
#include "command.h"
#include "component_animation.h"


namespace Commands
{
	class MovementAnimation : public Command
	{
		Components::Movement * movement_;
		Components::FrameAnimation * frame_animation_;
	public:
		MovementAnimation(Components::Movement *movement, Components::FrameAnimation * frame_animation);
		~MovementAnimation();

		void execute() override;
	};
}
