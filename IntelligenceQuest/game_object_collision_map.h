#pragma once

namespace GameObjects
{
	class CollisionMap : public GameObject
	{
		bool debug_;
		int scaled_size_, tile_size_, map_width_, map_height_;
		float tile_scale_;
		glm::vec2 position_;
		std::string tex_id_;
		std::size_t i_;
	public:
		CollisionMap(std::string tex_id, glm::vec2 position, int map_width, int map_height, int tile_size, float scale, bool debug);
		~CollisionMap();

		void render() override;
		void update() override;
		void clean() override;

		void add_collider(int x, int y, int src_x, int src_y);
	};
}