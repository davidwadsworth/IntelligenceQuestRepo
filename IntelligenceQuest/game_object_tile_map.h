#pragma once
#include "game_object.h"
#include <vec2.hpp>

namespace DataLoads
{
	class LTileMap;
}

namespace GameObjects
{
	class TileMap : public GameObject
	{
		std::vector<Entity*> tiles_;
		DataLoads::LTileMap* tile_map_load_;
		glm::vec2 position_;
		std::size_t tile_size_;
		float tile_scale_;
		const char * file_path_;
	public:
		std::size_t map_width;
		std::size_t map_height;
		int scaled_size;
		std::string tex_id;

		explicit TileMap(glm::vec2 position, const char * file_path, std::size_t tile_size, float tile_scale);
		~TileMap();
		void render() override;
		void clean() override;

		void add_tile(int src_x, int src_y, int x, int y, int rots, SDL_RendererFlip flp);

	};
}