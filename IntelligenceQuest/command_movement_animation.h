#pragma once
#include "command.h"
#include "component_animation.h"
#include "component_physics.h"

namespace Commands
{
	class MovementAnimation : public Command
	{
		Components::Physics * physics_;
		Components::FrameAnimation * frame_animation_;
	public:
		MovementAnimation(Components::Physics *physics, Components::FrameAnimation * frame_animation);
		~MovementAnimation();

		void execute() override;
	};
}
