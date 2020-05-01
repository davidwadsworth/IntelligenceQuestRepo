#pragma once
#include "collider.h"
#include "unruly.h"
#include <unordered_map>
#include "ecs.h"

constexpr std::size_t MAX_OBJECTS = 10;
constexpr std::size_t MAX_LEVELS = 5;
constexpr std::size_t MAX_INDEX = 4;
constexpr std::size_t MAX_KEYS = 64;

class QuadTree;

struct QuadTreeKey
{
	QuadTree* tree;
	std::size_t id;
};

class QuadTree
{
	enum 
	{
		top_left,
		top_right, 
		bot_right,
		bot_left
	};

	std::unordered_map<Entity*, unruly<QuadTreeKey, MAX_KEYS>>* entity_map_;
	glm::vec2 position_;
	int width_, height_;
	unruly<Entity*, MAX_OBJECTS> entities_;
	void split();
	std::size_t get_index(Entity* entity);
	void remove(int id);
	std::size_t level_;
	std::array<QuadTree*, MAX_INDEX> index_;
	QuadTree(int p_level, glm::vec2 position, int width, int height, std::unordered_map<Entity*, unruly<QuadTreeKey, MAX_KEYS>>* entity_map);
public:
	QuadTree(glm::vec2 position, int width, int height);
	~QuadTree();

	void delete_map();

	void refresh(Entity * entity);
	void clear();
	void insert(Entity* entity);
	void remove(Entity* entity);

	friend std::ostream& operator<<(std::ostream& os, const QuadTree& qt);
	std::vector<Entity*> retrieve(Entity * entity);
};
