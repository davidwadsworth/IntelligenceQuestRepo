#include "stdafx.h"
#include <fstream>
#include <vector>
#include <rapidxml.hpp>
#include "data_load_tiles.h"
#include <string.h>

extern Manager manager;

DataLoads::LTileMap::LTileMap(GameObjects::TileMap* tile_map, int map_scale, int tile_size)
	: tile_map_(tile_map), tile_size_(tile_size)
{
	scaled_size_ = tile_size * map_scale;
	tile_map_->scaled_size = scaled_size_;
}

DataLoads::LTileMap::~LTileMap()
{
}

void DataLoads::LTileMap::load(const char * path)
{
	std::ifstream mapFile (path);
	rapidxml::xml_document<> map;

	std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	map.parse<0>(&buffer[0]);

	const auto root_node = map.first_node("tilemap");
	tile_map_->tex_id = root_node->first_attribute("name")->value();
	tile_map_->map_width = atoi(root_node->first_attribute("tileswide")->value());
	tile_map_->map_height = atoi(root_node->first_attribute("tileshigh")->value());

	for (rapidxml::xml_node<> * layer_node = root_node->first_node("layer"); layer_node; layer_node = layer_node->next_sibling())
	{
		for (rapidxml::xml_node<> * tile_node = layer_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling())
		{
			auto flip = SDL_FLIP_NONE;

			const auto scaled_x = atoi(tile_node->first_attribute("x")->value()) * tile_map_->scaled_size;
			const auto scaled_y = atoi(tile_node->first_attribute("y")->value()) * tile_map_->scaled_size;


			const auto tile_id = atoi(tile_node->first_attribute("tile")->value());

			const auto src_x = (tile_id % 10) * tile_size_;
			const auto src_y = ((tile_id / 10)) * tile_size_;

			const auto rotations = atoi(tile_node->first_attribute("rot")->value());

			const char* flip_x = tile_node->first_attribute("flipX")->value();

			if (!strcmp(flip_x, "true"))
				flip = SDL_FLIP_HORIZONTAL;

			tile_map_->add_tile(src_x, src_y, scaled_x, scaled_y, rotations, flip);
		}
	}
}





