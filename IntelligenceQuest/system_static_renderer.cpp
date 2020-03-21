#include "stdafx.h"
#include "system_static_renderer.h"

RenderSystems::StaticRenderer::StaticRenderer() = default;
RenderSystems::StaticRenderer::~StaticRenderer() = default;

void RenderSystems::StaticRenderer::update()
{
	for (auto g : get_grouped_entities()) 
		for(auto& e : *g)
		{
			const auto render = e->getComponent<Components::Render>();
			TextureManager::draw(render.texture, render.src, render.dest);
		}
}
