#include "stdafx.h"
#include "component_render.h"


Components::Render::Render(const std::string id, SDL_Rect* dest)
	: src(nullptr), dest(dest), rotation_point(nullptr), rotation(0.0f), flip(SDL_FLIP_NONE)
{
	set_tex(id);
}

Components::Render::Render(std::string id, SDL_Rect * dest, SDL_Rect * src)
	: src(src), dest(dest), rotation_point(nullptr), rotation(0), flip(SDL_FLIP_NONE)
{
	set_tex(id);
}

Components::Render::Render(const std::string id, SDL_Rect* dest, SDL_Rect* src, SDL_Point * rot_point, const double rot, const SDL_RendererFlip flip)
	: src(src), dest(dest), rotation_point(rot_point), rotation(rot), flip(flip)
{
	set_tex(id);
}

Components::Render::~Render() = default;

void Components::Render::set_tex(const std::string id) 
{
	texture = Game::assets->GetTexture(id);
}



