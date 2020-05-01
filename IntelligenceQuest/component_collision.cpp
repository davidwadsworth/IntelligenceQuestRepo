#include "stdafx.h"

Components::Collision::Collision(std::string t, QuadTree* collision_tree, Collider * collider)
	: tag(t), collision_tree_(collision_tree), collider_(collider)
{}

Components::Collision::~Collision()
{
	delete collider_;
}

Collider * Components::Collision::get_collider()
{
	return collider_;
}

QuadTree * Components::Collision::get_collision_tree()
{
	return collision_tree_;
}
