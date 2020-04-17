#include "stdafx.h"

Components::Collision::Collision(std::string t, Collider * collider)
	: tag(t), collider_(collider)
{}

Components::Collision::~Collision()
{
	delete collider_;
}

Collider * Components::Collision::get_collider()
{
	return collider_;
}
