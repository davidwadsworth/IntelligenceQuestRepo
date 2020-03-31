#pragma once
#include <string>
#include <SDL.h>
#include "game_object_tile_map.h"
#include "data_load.h"

namespace DataLoads
{
	class LTileMap : public DataLoad
	{
	public:
		LTileMap(GameObjects::TileMap * tile_map, int map_scale, int tile_size);
		~LTileMap();

		void load(const char* path) override;
		void add_tile(int src_x, int src_y, int x, int y, int rots, SDL_RendererFlip flp);
	private:
		GameObjects::TileMap * tile_map_;
		int scaled_size_;
		int tile_size_;
	};
}
