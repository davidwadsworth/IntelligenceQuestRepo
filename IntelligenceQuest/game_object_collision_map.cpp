#include "stdafx.h"
#include "component_collision.h"
#include "game_object_collision_map.h"
#include "command_render_dynamic.h"
#include "collision_world.h"
#include "collider_polygon.h"
#include "collider_boundary.h"

GameObjects::CollisionMap::CollisionMap(std::string tex_id, glm::vec2 position, int map_width, int map_height, int tile_size, float scale, bool debug)
	: tex_id_(tex_id), debug_(debug), map_width_(map_width), map_height_(map_height), position_(position), tile_size_(tile_size), tile_scale_(scale), i_(0)
{
	scaled_size_ = tile_size_ * tile_scale_;
	this->add_group(Game::group_colliders);

	auto& collider = Manager::add_entity();
	auto transform = &collider.add_component<Components::Transform>(800, 640, tile_size_, tile_size_, tile_scale_);
	auto render = &collider.add_component<Components::Render>(tex_id_, new SDL_Rect{ 800, 640, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 32, tile_size_, tile_size_ });
	auto collision = &collider.add_component<Components::Collision>("triangle", new Colliders::Polygon(&transform->position, { glm::vec2(0, 0), glm::vec2(scaled_size_, 0), glm::vec2(0, scaled_size_) }));

	add_render_command(new RenderCommands::Dynamic(render, transform));

	CollisionWorld::insert(&collider);

	auto& collider2 = Manager::add_entity();
	auto transform2 = &collider2.add_component<Components::Transform>(704, 736, tile_size_, tile_size_, tile_scale_);
	auto render2 = &collider2.add_component<Components::Render>(tex_id_, new SDL_Rect{ 704, 736, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 32, tile_size_, tile_size_ });
	auto collision2 = &collider2.add_component<Components::Collision>("triangle", new Colliders::Polygon(&transform2->position, { glm::vec2(0, 0), glm::vec2(scaled_size_, 0), glm::vec2(0, scaled_size_) }));

	add_render_command(new RenderCommands::Dynamic(render2, transform2));

	CollisionWorld::insert(&collider2);

	auto& collider3 = Manager::add_entity();
	auto transform3 = &collider3.add_component<Components::Transform>(800, 1000, tile_size_, tile_size_, tile_scale_);
	auto render3 = &collider3.add_component<Components::Render>(tex_id_, new SDL_Rect{ 1200, 640, scaled_size_, scaled_size_ }, new SDL_Rect{ 128, 128, tile_size_, tile_size_ });
	auto collision3 = &collider3.add_component<Components::Collision>("circle", new Colliders::Circle(&transform3->position, 48));

	add_render_command(new RenderCommands::Dynamic(render3, transform3));

	CollisionWorld::insert(&collider3);

	auto& collider4 = Manager::add_entity();
	auto transform4 = &collider4.add_component<Components::Transform>(610, 832, tile_size_, tile_size_, tile_scale_);
	auto render4 = &collider4.add_component<Components::Render>(tex_id_, new SDL_Rect{ 610, 832, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 64, tile_size_, tile_size_ });
	auto collision4 = &collider4.add_component<Components::Collision>("boundary", new Colliders::Boundary(&transform4->position, { glm::vec2(0, scaled_size_), glm::vec2(scaled_size_, 0) }));

	add_render_command(new RenderCommands::Dynamic(render4, transform4));

	CollisionWorld::insert(&collider4);

	auto& collider5 = Manager::add_entity();
	auto transform5 = &collider5.add_component<Components::Transform>(514, 928, tile_size_, tile_size_, tile_scale_);
	auto render5 = &collider5.add_component<Components::Render>(tex_id_, new SDL_Rect{ 514, 928, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 64, tile_size_, tile_size_ });
	auto collision5 = &collider5.add_component<Components::Collision>("boundary", new Colliders::Boundary(&transform5->position, {glm::vec2(0, scaled_size_), glm::vec2(scaled_size_, 0)}));

	add_render_command(new RenderCommands::Dynamic(render5, transform5));

	CollisionWorld::insert(&collider5);
}

GameObjects::CollisionMap::~CollisionMap()
{
	this->remove_group(Game::group_colliders);
	this->deactivate();
}

void GameObjects::CollisionMap::render()
{
	if (!debug_) return;
	GameObject::render();
}

void GameObjects::CollisionMap::update()
{
	GameObject::update();
}

void GameObjects::CollisionMap::clean()
{}

void GameObjects::CollisionMap::add_collider(int x, int y, int src_x, int src_y)
{
	auto& collider = Manager::add_entity();
	const auto transform = &collider.add_component<Components::Transform>(x + position_.x, y + position_.y, tile_size_, tile_size_, tile_scale_);
	const auto render = &collider.add_component<Components::Render>(tex_id_, new SDL_Rect{ static_cast<int>(x + position_.x), static_cast<int>(y + position_.y), scaled_size_, scaled_size_ }, new SDL_Rect{ src_x, src_y, tile_size_, tile_size_ });
	auto half_scaled_size = scaled_size_ / 2.0f;
	const auto collision = &collider.add_component<Components::Collision>("aabb", new Colliders::Polygon(&transform->position, { glm::vec2(0, 0), glm::vec2(scaled_size_, 0), glm::vec2(scaled_size_, scaled_size_), glm::vec2(0, scaled_size_) }));

	add_render_command(new RenderCommands::Dynamic(render, transform));

	CollisionWorld::insert(&collider);
}