#include "stdafx.h"
#include "command_static_render.h"
#include "command_dynamic_render.h"

Commands::StaticRender::StaticRender(Components::Render* render)
	: render_(render)
{}


Commands::StaticRender::~StaticRender() = default;

void Commands::StaticRender::execute()
{
	TextureManager::draw(render_->texture, render_->src, render_->dest);
}
