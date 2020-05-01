#include "stdafx.h"
#include "component_collision.h"
#include "game_object_collision_map.h"
#include "command_render_dynamic.h"
#include "collider_polygon.h"
#include "collider_boundary.h"
#include "collider_circle.h"
#include "command_refresh_quad_tree.h"

GameObjects::CollisionMap::CollisionMap(std::string tex_id, QuadTree* collision_tree, glm::vec2 position, int map_width, int map_height, int tile_size, float scale, bool debug)
	: tex_id_(tex_id), debug_(debug), map_width_(map_width), map_height_(map_height), position_(position), tile_size_(tile_size), tile_scale_(scale), i_(0), collision_tree_(collision_tree)
{
	scaled_size_ = tile_size_ * tile_scale_;
	if (debug_)
	{
		render_tree_ = new QuadTree(position_, map_width_ * scaled_size_, map_height_* scaled_size_);
		render_tree_->insert(Game::camera->entity);
		this->add_update_command(new Commands::RefreshQuadTree(Game::camera->entity, render_tree_));
	}
		
	this->add_group(Game::group_colliders);

	auto& collider = Manager::add_entity();
	auto transform = &collider.add_component<Components::Transform>(800, 640, tile_size_, tile_size_, tile_scale_);
	auto render = &collider.add_component<Components::Render>(tex_id_, new SDL_Rect{ 800, 640, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 32, tile_size_, tile_size_ });
	auto collision = &collider.add_component<Components::Collision>("triangle", collision_tree_, new Colliders::Polygon(&transform->position, { glm::vec2(0, 0), glm::vec2(scaled_size_, 0), glm::vec2(0, scaled_size_) }));
	
	render_tree_->insert(&collider);
	collision_tree_->insert(&collider);

	auto& collider2 = Manager::add_entity();
	auto transform2 = &collider2.add_component<Components::Transform>(704, 736, tile_size_, tile_size_, tile_scale_);
	auto render2 = &collider2.add_component<Components::Render>(tex_id_, new SDL_Rect{ 704, 736, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 32, tile_size_, tile_size_ });
	auto collision2 = &collider2.add_component<Components::Collision>("triangle", collision_tree_, new Colliders::Polygon(&transform2->position, { glm::vec2(0, 0), glm::vec2(scaled_size_, 0), glm::vec2(0, scaled_size_) }));

	render_tree_->insert(&collider2);
	collision_tree_->insert(&collider2);

	auto& collider3 = Manager::add_entity();
	auto transform3 = &collider3.add_component<Components::Transform>(800, 1000, tile_size_, tile_size_, tile_scale_);
	auto render3 = &collider3.add_component<Components::Render>(tex_id_, new SDL_Rect{ 1200, 640, scaled_size_, scaled_size_ }, new SDL_Rect{ 128, 128, tile_size_, tile_size_ });
	auto collision3 = &collider3.add_component<Components::Collision>("circle", collision_tree_, new Colliders::Circle(&transform3->position, 48));

	render_tree_->insert(&collider3);
	collision_tree_->insert(&collider3);

	auto& collider4 = Manager::add_entity();
	auto transform4 = &collider4.add_component<Components::Transform>(610, 832, tile_size_, tile_size_, tile_scale_);
	auto render4 = &collider4.add_component<Components::Render>(tex_id_, new SDL_Rect{ 610, 832, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 64, tile_size_, tile_size_ });
	auto collision4 = &collider4.add_component<Components::Collision>("boundary", collision_tree_, new Colliders::Boundary(&transform4->position, { glm::vec2(0, scaled_size_), glm::vec2(scaled_size_, 0) }));

	render_tree_->insert(&collider4);
	collision_tree_->insert(&collider4);

	auto& collider5 = Manager::add_entity();
	auto transform5 = &collider5.add_component<Components::Transform>(514, 928, tile_size_, tile_size_, tile_scale_);
	auto render5 = &collider5.add_component<Components::Render>(tex_id_, new SDL_Rect{ 514, 928, scaled_size_, scaled_size_ }, new SDL_Rect{ 32, 64, tile_size_, tile_size_ });
	auto collision5 = &collider5.add_component<Components::Collision>("boundary", collision_tree_, new Colliders::Boundary(&transform5->position, {glm::vec2(0, scaled_size_), glm::vec2(scaled_size_, 0)}));

	render_tree_->insert(&collider5);
	collision_tree_->insert(&collider5);
}


GameObjects::CollisionMap::~CollisionMap()
{
	if (debug_)
	{
		render_tree_->delete_map();
		delete render_tree_;
		render_tree_ = nullptr;
	}

	this->remove_group(Game::group_colliders);
	this->deactivate();
}

void GameObjects::CollisionMap::render()
{
	if (!debug_)
		return;

	auto entities = render_tree_->retrieve(Game::camera->entity);

	if (!(SDL_GetTicks() % 1000))
		std::cout << entities.size() << std::endl;

	for (auto e : entities)
	{
		auto render = RenderCommands::Dynamic( &e->get_component<Components::Render>(), &e->get_component<Components::Transform>());
		render.execute();
	}
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
	const auto collision = &collider.add_component<Components::Collision>(tex_id_, collision_tree_, new Colliders::Polygon(&transform->position, { glm::vec2(0, 0), glm::vec2(scaled_size_, 0), glm::vec2(scaled_size_, scaled_size_), glm::vec2(0, scaled_size_) }));

	if (debug_)
	{
		const auto render = &collider.add_component<Components::Render>(tex_id_, new SDL_Rect{ static_cast<int>(x + position_.x), static_cast<int>(y + position_.y), scaled_size_, scaled_size_ }, new SDL_Rect{ src_x, src_y, tile_size_, tile_size_ });
		render_tree_->insert(&collider);
	}

	collision_tree_->insert(&collider);
}