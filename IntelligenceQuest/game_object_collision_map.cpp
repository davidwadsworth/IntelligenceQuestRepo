#include "stdafx.h"
#include "component_collision.h"
#include "game_object_collision_map.h"
#include "command_render_dynamic.h"
#include "collision_world.h"
#include "collider_polygon.h"

GameObjects::CollisionMap::CollisionMap(std::string tex_id, glm::vec2 position, int map_width, int map_height, int tile_size, float scale, bool debug)
	: tex_id_(tex_id), debug_(debug), map_width_(map_width), map_height_(map_height), position_(position), tile_size_(tile_size), tile_scale_(scale), i_(0)
{
	scaled_size_ = tile_size_ * tile_scale_;
	this->add_group(Game::group_colliders);

	auto& collider = Manager::add_entity();
	const auto transform = &collider.add_component<Components::Transform>(800, 640, tile_size_, tile_size_, tile_scale_);
	const auto render = &collider.add_component<Components::Render>(tex_id_, new SDL_Rect{ 800, 640, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 32, tile_size_, tile_size_ });
	auto half_scaled_size = scaled_size_ / 2.0f;
	const auto collision = &collider.add_component<Components::Collision>("aabb", new Colliders::Polygon(&transform->position, { glm::vec2(-half_scaled_size, -half_scaled_size), glm::vec2(half_scaled_size, -half_scaled_size), glm::vec2(half_scaled_size, half_scaled_size) }));

	add_render_command(new RenderCommands::Dynamic(render, transform));

	CollisionWorld::insert(&collider);
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
	const auto collision = &collider.add_component<Components::Collision>("aabb", new Colliders::Polygon(&transform->position, { glm::vec2(-half_scaled_size, -half_scaled_size), glm::vec2(half_scaled_size, -half_scaled_size), glm::vec2(half_scaled_size, half_scaled_size), glm::vec2(-half_scaled_size, half_scaled_size) }));

	add_render_command(new RenderCommands::Dynamic(render, transform));

	CollisionWorld::insert(&collider);
}