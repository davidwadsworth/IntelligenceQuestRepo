#include "stdafx.h"
#include "command_render_static.h"

RenderCommands::Static::Static(Components::Render* render)
	: render_(render)
{}


RenderCommands::Static::~Static() = default;

void RenderCommands::Static::execute()
{
	TextureManager::draw(render_->texture, render_->src, render_->dest);
}
