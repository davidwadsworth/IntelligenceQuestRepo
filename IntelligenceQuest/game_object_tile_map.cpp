#include "stdafx.h"
#include "game_object_tile_map.h"
#include "command_dynamic_render.h"

GameObjects::TileMap::TileMap(const glm::vec2 position, const char * file_path, const std::size_t tile_size, const float tile_scale)
	: position_(position), tile_size_(tile_size), tile_scale_(tile_scale), file_path_(file_path)
{
	tile_map_load_ = new DataLoads::LTileMap(this, tile_scale_, tile_size_);
	tile_map_load_->load(file_path_);
	this->add_group(Game::group_map);
}

GameObjects::TileMap::~TileMap()
{
	delete tile_map_load_;
	this->remove_group(Game::group_map);
	this->deactivate();
}

void GameObjects::TileMap::render()
{
	if (is_render_paused()) return;

	const unsigned col_start = Game::camera.y / scaled_size;
	const unsigned row_start = Game::camera.x / scaled_size;

	auto col_end = col_start + Game::SCREEN_HEIGHT / scaled_size + (Game::SCREEN_HEIGHT % scaled_size != 0);
	col_end = col_end == map_height ? col_end - 1 : col_end;
	auto row_end = row_start + Game::SCREEN_WIDTH / scaled_size + (Game::SCREEN_WIDTH % scaled_size != 0);
	row_end = row_end == map_width ? row_end - 1 : row_end;
	
	for (auto i = col_start * map_width; i <= col_end * map_width; i += map_width)
		for (auto j = i + row_start; j <= i + row_end; j++)
			(*get_render_commands())[j]->execute();
}

void GameObjects::TileMap::clean()
{}

void GameObjects::TileMap::add_tile(const int src_x, const int src_y, const int x, const int y, const int rots, SDL_RendererFlip flp)
{
	auto& tile(Manager::add_entity());
	const auto transform = &tile.add_component<Components::Transform>(x + position_.x, y + position_.y, tile_size_, tile_size_, tile_scale_);
	const auto render = &tile.add_component<Components::Render>(tex_id, new SDL_Rect{ x, y, scaled_size, scaled_size }, new SDL_Rect{ src_x, src_y, 32, 32 }, nullptr, static_cast<float>(rots * 90), flp);
	tiles_.push_back(&tile);
	add_render_command(new Commands::DynamicRender(render, transform));
}