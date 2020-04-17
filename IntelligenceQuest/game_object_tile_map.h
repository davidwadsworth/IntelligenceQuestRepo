#pragma once
#include "game_object.h"
#include <vec2.hpp>
#include <vector>

namespace DataLoads
{
	class LTileMap;
}

namespace GameObjects
{
	class TileMap : public GameObject
	{
		std::vector<Entity*> tiles_; // TODO change to static allocation
		glm::vec2 position_;
		std::size_t map_width_, map_height_;
		int tile_size_, scaled_size_;
		float tile_scale_;
		std::string tex_id_;
	public:

		explicit TileMap(std::string tex_id, glm::vec2 position, std::size_t map_width, std::size_t map_height, int tile_size, float scale);
		~TileMap();
		void render() override;
		void clean() override;

		void add_tile(int src_x, int src_y, int x, int y, int rots, SDL_RendererFlip flp);
	};
}