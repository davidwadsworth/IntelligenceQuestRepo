#include "stdafx.h"
#include "component_movement.h"

Components::Movement::Movement(float speed)
	: direction(0, 0), speed(speed)
{}

Components::Movement::~Movement() = default;
