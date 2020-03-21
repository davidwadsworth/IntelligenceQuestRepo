#include "stdafx.h"
#include "system_animation.h"
#include "component_animation.h"

UpdateSystems::Animation::Animation() = default;
UpdateSystems::Animation::~Animation() = default;

void UpdateSystems::Animation::update()
{
	for (auto g : get_grouped_entities())
		for (auto& e : *g)
		{
			const auto anim = &e->getComponent<Components::FrameAnimation>();
			const auto render = &e->getComponent<Components::Render>();
			const auto fr_anim = anim->get_animate_state();

			if (anim->is_animated)
				render->src->x = render->src->w * static_cast<int>(SDL_GetTicks() / fr_anim->speed % fr_anim->frames) + render->src->w;
			else
				render->src->x = 0;

			render->src->y = fr_anim->index * render->src->w;
		}
}
