#include "stdafx.h"
#include "quad_tree.h"

std::size_t QuadTree::get_index(Entity* entity)
{
	auto vertical_midpoint = position_.x + (width_ / 2);
	auto horizontal_midpoint = position_.y + (height_ / 2);

	auto transform = &entity->get_component<Components::Transform>();
	auto x = transform->position.x;
	auto y = transform->position.y;
	auto w = transform->width * transform->scale;
	auto h = transform->height * transform->scale;

//	std::cout << x << ", " << y << std::endl;

	auto top_quadrant = y < horizontal_midpoint;
	auto bottom_quadrant = y + h > horizontal_midpoint;

	auto left_quadrant = x < vertical_midpoint;
	auto right_quadrant = x + w > vertical_midpoint;

	auto i = 0u;
	auto index = 0u;

	if (left_quadrant) {
		if (top_quadrant) index += top_left << (i++ << 1u);
		if (bottom_quadrant) index += bot_left << (i++ << 1u);
	}
	if (right_quadrant) {
		if (top_quadrant) index += top_right << (i++ << 1u);
		if (bottom_quadrant) index += bot_right << (i++ << 1u);
	}
	return index;
}

void QuadTree::split()
{
	auto subWidth = width_ / 2;
	auto subHeight = height_ / 2;
	auto x = position_.x;
	auto y = position_.y;

	index_[top_left] = new QuadTree(level_ + 1, glm::vec2(x, y), subWidth, subHeight, entity_map_);
	index_[top_right] = new QuadTree(level_ + 1, glm::vec2( x + subWidth, y), subWidth, subHeight, entity_map_ );
	index_[bot_right] = new QuadTree(level_ + 1, glm::vec2( x + subWidth, y + subHeight), subWidth, subHeight, entity_map_ );
	index_[bot_left] = new QuadTree(level_ + 1, glm::vec2( x, y + subHeight), subWidth, subHeight, entity_map_ );
}

QuadTree::QuadTree(glm::vec2 position, int width, int height)
	: level_(0), position_(position), width_(width), height_(height), index_{0}, entity_map_(new std::unordered_map<Entity*, unruly<QuadTreeKey, MAX_INDEX>>())
{}

QuadTree::QuadTree(int level, glm::vec2 position, int width, int height, std::unordered_map<Entity*, unruly<QuadTreeKey, MAX_INDEX>>* entity_map)
	: level_(level), position_(position), width_(width), height_(height), index_{ 0 }, entity_map_(entity_map)
{}

QuadTree::~QuadTree()
{
	this->clear();
	if (entity_map_)
	{
		entity_map_->clear();
		delete entity_map_;
		entity_map_ = nullptr;
	}
}

void QuadTree::refresh(Entity * entity)
{
	auto keys = &(*entity_map_)[entity];

	for (auto i = 0; i < keys->size; i++)
		(*keys)[i].tree->remove((*keys)[i].id);
	keys->clear();

	insert(entity);
}

void QuadTree::clear()
{
	for (auto i : index_)
	{
		i->clear();
		delete i;
		i = nullptr;
	}
}

void QuadTree::remove(int id)
{
	entities_.remove(id);
}

void QuadTree::insert(Entity* entity)
{
	if (entities_.size >= MAX_OBJECTS && level_ < MAX_LEVELS) {
		split();
		for (auto i = 0; i < entities_.size; i++)
			for (auto index = get_index(entities_[i]);;)
			{
				index_[(index % MAX_INDEX)]->insert(entities_[i]);
				index >>= 2;
				if (!index) break;
			}
		entities_.clear();
	}

	if (index_[top_left])
		for (auto index = get_index(entity);;) {
			index_[(index % MAX_INDEX)]->insert(entity);
			index >>= 2;
			if (!index) return;
		}

	entities_.push_back(entity);
	(*entity_map_)[entity].push_back(QuadTreeKey{ this, entities_.size - 1 });

}

std::vector<Entity*> QuadTree::retrieve(Entity * entity)
{
	std::vector<Entity*> retrieved_entities;

	auto leaves = (*entity_map_)[entity];

	for (auto i = 0; i < leaves.size; i++)
		for (auto e : leaves[i].tree->entities_)
			retrieved_entities.push_back(e);

	return retrieved_entities;
}

std::ostream & operator<<(std::ostream & os, const QuadTree & qt)
{
	os << std::endl;

	if (qt.index_[qt.top_left])
	{
		os << std::string(qt.level_, '\t') << "top left " << *qt.index_[qt.top_left];
		os << std::string(qt.level_, '\t') << "top right " << *qt.index_[qt.top_right];
		os << std::string(qt.level_, '\t') << "bot right " << *qt.index_[qt.bot_right];
		os << std::string(qt.level_, '\t') << "bot left " << *qt.index_[qt.bot_left];
	}

	for (auto i = 0; i < qt.entities_.size; i++)
	{
		auto transform = qt.entities_.buffer[i]->get_component<Components::Transform>();
		os << std::string(qt.level_, '\t') << "(" << transform.position.x << ", " << transform.position.y << ", " << transform.width * transform.scale << ", " << transform.height * transform.scale << ")" << std::endl;
	}

	return os;
}
