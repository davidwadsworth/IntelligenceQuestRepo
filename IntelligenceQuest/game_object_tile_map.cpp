#include "stdafx.h"
#include "game_object_tile_map.h"
#include "command_render_dynamic.h"

GameObjects::TileMap::TileMap(std::string tex_id, glm::vec2 position, std::size_t map_width, std::size_t map_height, int tile_size, float scale)
	: tex_id_(tex_id), position_(position), map_width_(map_width), map_height_(map_height), tile_size_(tile_size), tile_scale_(scale)
{
	scaled_size_ = tile_size_ * tile_scale_;
	this->add_group(Game::group_map);
}

GameObjects::TileMap::~TileMap()
{
	this->remove_group(Game::group_map);
	this->deactivate();
}

void GameObjects::TileMap::render()
{
	if (is_render_paused()) return;

	const unsigned col_start = Game::camera->transform->position.y / scaled_size_;
	const unsigned row_start = Game::camera->transform->position.x / scaled_size_;

	auto col_end = col_start + Game::SCREEN_HEIGHT / scaled_size_ + (Game::SCREEN_HEIGHT % scaled_size_ != 0);
	col_end = col_end == map_height_ ? col_end - 1 : col_end;
	auto row_end = row_start + Game::SCREEN_WIDTH / scaled_size_ + (Game::SCREEN_WIDTH % scaled_size_ != 0);
	row_end = row_end == map_width_ ? row_end - 1 : row_end;
	
	for (auto i = col_start * map_width_; i <= col_end * map_width_; i += map_width_)
		for (auto j = i + row_start; j <= i + row_end; j++)
			(*get_render_commands())[j]->execute();
}

void GameObjects::TileMap::clean()
{}

void GameObjects::TileMap::add_tile(const int src_x, const int src_y, const int x, const int y, const int rots, SDL_RendererFlip flp)
{
	auto& tile(Manager::add_entity());
	const auto transform = &tile.add_component<Components::Transform>(x + position_.x, y + position_.y, tile_size_, tile_size_, tile_scale_);
	const auto render = &tile.add_component<Components::Render>(tex_id_, new SDL_Rect{ static_cast<int>(x + position_.x), static_cast<int>(y + position_.y), scaled_size_, scaled_size_ }, new SDL_Rect{ src_x, src_y, tile_size_, tile_size_ }, nullptr, static_cast<float>(rots * 90), flp);
	tiles_.push_back(&tile);
	add_render_command(new RenderCommands::Dynamic(render, transform));
}