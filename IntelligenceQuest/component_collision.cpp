#include "stdafx.h"
#include "component_collision.h"

Components::Collision::Collision(std::string t)
	: tag(t)
{}

Components::Collision::Collision(std::string t, int x, int y, int size)
	: tag(t)
{}

Components::Collision::~Collision() = default;



