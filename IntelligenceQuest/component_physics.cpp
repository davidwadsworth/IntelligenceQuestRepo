#include "stdafx.h"
#include "component_physics.h"

Components::Physics::Physics(int mass)
	: mass(mass), force(), prev_force()
{}

Components::Physics::~Physics() = default;
