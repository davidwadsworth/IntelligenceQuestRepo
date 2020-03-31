#include "stdafx.h"
#include "component_animation.h"
#define SPEED 200


Components::FrameAnimation::FrameAnimation()
	: is_animated(false)
{
	auto walk_down = FrameAnimate(0, 2, SPEED);
	auto walk_up = FrameAnimate(1, 2, SPEED);
	auto walk_right = FrameAnimate(2, 2, SPEED);
	auto walk_down_right = FrameAnimate(3, 2, SPEED);
	auto walk_up_right = FrameAnimate(4, 2, SPEED);
	auto walk_left = FrameAnimate(5, 2, SPEED);
	auto walk_down_left = FrameAnimate(6, 2, SPEED);
	auto walk_up_left = FrameAnimate(7, 2, SPEED);

	anim_map_.emplace("walk down", walk_down);
	anim_map_.emplace("walk up", walk_up);
	anim_map_.emplace("walk right", walk_right);
	anim_map_.emplace("walk down right", walk_down_right);
	anim_map_.emplace("walk up right", walk_up_right);
	anim_map_.emplace("walk left", walk_left);
	anim_map_.emplace("walk down left", walk_down_left);
	anim_map_.emplace("walk up left", walk_up_left);

	current_ = &anim_map_["walk_down"];
}

Components::FrameAnimation::~FrameAnimation()
{}

void Components::FrameAnimation::add_animation(const char * anim_id, FrameAnimate anim)
{
	anim_map_.emplace(anim_id, anim);
}

void Components::FrameAnimation::play(const char * anim)
{
	current_ = &anim_map_[anim];
}

FrameAnimate * Components::FrameAnimation::get_animate_state() const
{
	return current_;
}

