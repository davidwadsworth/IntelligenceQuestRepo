#pragma once
#include "command.h"
#include "component_animation.h"


namespace Commands
{
	class FrameAnimation : public Command
	{
		Components::FrameAnimation * frame_animation_;
		Components::Render * render_;
	public:
		FrameAnimation(Components::FrameAnimation * frame_animation, Components::Render * render);
		~FrameAnimation();

		void execute() override;
	};
}
