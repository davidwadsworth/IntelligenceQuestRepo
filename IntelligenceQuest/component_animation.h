#pragma once

#include "ECS.h"
#include "animate.h"

namespace Components
{
	class FrameAnimation : public Component
	{
		std::map<const char *, FrameAnimate> anim_map_;
		FrameAnimate * current_;
	public:
		bool is_animated;
		explicit FrameAnimation();
		~FrameAnimation();
		void add_animation(const char * anim_id, FrameAnimate anim);
		void play(const char * anim);
		FrameAnimate* get_animate_state() const;
	};
}