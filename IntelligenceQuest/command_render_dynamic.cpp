#include "stdafx.h"
#include "command_render_dynamic.h"

RenderCommands::Dynamic::Dynamic(Components::Render* render, Components::Transform* transform)
	: render_(render), transform_(transform)
{}

RenderCommands::Dynamic::~Dynamic() = default;

void RenderCommands::Dynamic::execute()
{
	render_->dest->w = static_cast<int>(transform_->width * transform_->scale);
	render_->dest->h = static_cast<int>(transform_->height * transform_->scale);
	render_->dest->x = std::round(transform_->position.x - Game::camera->transform->position.x);
	render_->dest->y = std::round(transform_->position.y - Game::camera->transform->position.y);

	TextureManager::draw(render_->texture, render_->src, render_->dest, render_->rotation, render_->rotation_point, render_->flip);
}
