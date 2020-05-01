#pragma once
#include <string>
#include <SDL.h>
#include "game_object_tile_map.h"
#include "data_load.h"
#include "game_object_collision_map.h"

namespace DataLoads
{
	class LTileMap : public DataLoad
	{
	public:
		LTileMap(std::string tex_id, QuadTree** collision_tree, glm::vec2 position, float scale, bool debug);
		~LTileMap();

		int scaled_size, map_width, map_height;

		void load(const char* path) override;
	private:
		QuadTree** collision_tree_;
		GameObjects::TileMap * tile_map_;
		GameObjects::CollisionMap * collision_map_;
		std::string tex_id_;
		glm::vec2 position_;
		bool debug_;
		int tile_size_;
		float scale_;
	};
}
