#include "stdafx.h"
#include "system_dynamic_renderer.h"


RenderSystems::DynamicRenderer::DynamicRenderer() = default;

RenderSystems::DynamicRenderer::~DynamicRenderer() = default;


void RenderSystems::DynamicRenderer::update()
{
	for (auto g : get_grouped_entities())
		for(auto& e : *g)
		{
			const auto render = &e->getComponent<Components::Render>();
			const auto transform = e->getComponent<Components::Transform>();

			auto trans_rect = SDL_Rect{ static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), transform.width, transform.height };
			auto port_view = SDL_Rect{ Game::camera.x - Game::SCREEN_WIDTH, Game::camera.y - Game::SCREEN_HEIGHT, Game::SCREEN_WIDTH * 2, Game::SCREEN_HEIGHT* 2 };

			if (BoxCollider2D::AABB(trans_rect, port_view))
			{
				render->dest->w = std::round(transform.width * transform.scale);
				render->dest->h = std::round(transform.height * transform.scale);
				render->dest->x = std::round(transform.position.x) - Game::camera.x;
				render->dest->y = std::round(transform.position.y) - Game::camera.y;
				TextureManager::draw(render->texture, render->src, render->dest, render->rotation, render->rotation_point, render->flip);
			}
		}
}
