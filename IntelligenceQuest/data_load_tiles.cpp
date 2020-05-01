#include "stdafx.h"
#include <fstream>
#include <vector>
#include <rapidxml.hpp>
#include "data_load_tiles.h"
#include <string.h>

extern Manager manager;

DataLoads::LTileMap::LTileMap(std::string tex_id, QuadTree** collision_tree, glm::vec2 position, float scale, bool debug)
	: tex_id_(tex_id), collision_tree_(collision_tree), position_(position), tile_size_ (0), scaled_size(0), scale_(scale), tile_map_(nullptr), debug_(debug), collision_map_(nullptr)
{}

DataLoads::LTileMap::~LTileMap() = default;

void DataLoads::LTileMap::load(const char * path)
{
	std::ifstream mapFile (path);
	rapidxml::xml_document<> map;

	std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	map.parse<0>(&buffer[0]);

	const auto root_node = map.first_node("tilemap");

	map_width = atoi(root_node->first_attribute("tileswide")->value());
	map_height = atoi(root_node->first_attribute("tileshigh")->value());
	tile_size_ = atoi(root_node->first_attribute("tilewidth")->value());

	scaled_size = tile_size_ * scale_;
	auto layer_node = root_node->first_node("layer");
	tile_map_ = new GameObjects::TileMap(tex_id_, position_, map_width, map_height, tile_size_, scale_);
	
	for (rapidxml::xml_node<> * tile_node = layer_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling())
	{
		auto flip = SDL_FLIP_NONE;

		const auto scaled_x = atoi(tile_node->first_attribute("x")->value()) * scaled_size;
		const auto scaled_y = atoi(tile_node->first_attribute("y")->value()) * scaled_size;

		const auto tile_id = atoi(tile_node->first_attribute("tile")->value());

		const auto src_x = tile_id % 10 * tile_size_;
		const auto src_y = tile_id / 10 * tile_size_;

		const auto rotations = atoi(tile_node->first_attribute("rot")->value());

		const char* flip_x = tile_node->first_attribute("flipX")->value();

		if (!strcmp(flip_x, "true"))
			flip = SDL_FLIP_HORIZONTAL;

		tile_map_->add_tile(src_x, src_y, scaled_x, scaled_y, rotations, flip);
	}

	layer_node = layer_node->next_sibling();
	if (layer_node)
	{
		(*collision_tree_) = new QuadTree(position_, map_width * scaled_size, map_height * scaled_size);
		collision_map_ = new GameObjects::CollisionMap(tex_id_, *collision_tree_, position_, map_width, map_height, tile_size_, scale_, debug_);
		for (rapidxml::xml_node<> * tile_node = layer_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling())
		{
			const auto scaled_x = atoi(tile_node->first_attribute("x")->value()) * scaled_size;
			const auto scaled_y = atoi(tile_node->first_attribute("y")->value()) * scaled_size;

			const auto tile_id = atoi(tile_node->first_attribute("tile")->value());

			if (tile_id >= 0)
			{
				const auto src_x = tile_id % 10 * tile_size_;
				const auto src_y = tile_id / 10 * tile_size_;

				collision_map_->add_collider(scaled_x, scaled_y, src_x, src_y);
			}
		}
	}
}





