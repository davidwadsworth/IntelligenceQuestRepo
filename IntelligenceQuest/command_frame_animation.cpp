#include "stdafx.h"
#include "command_frame_animation.h"

Commands::FrameAnimation::FrameAnimation(Components::FrameAnimation *frame_animation, Components::Render * render)
	: frame_animation_(frame_animation), render_(render)
{}

Commands::FrameAnimation::~FrameAnimation() = default;

void Commands::FrameAnimation::execute()
{
	const auto animate = frame_animation_->get_animate_state();

	if (frame_animation_->is_animated)
		render_->src->x = render_->src->w * static_cast<int>(SDL_GetTicks() / animate->speed % animate->frames) + render_->src->w;
	else
		render_->src->x = 0;

	render_->src->y = animate->index * render_->src->w;
}

