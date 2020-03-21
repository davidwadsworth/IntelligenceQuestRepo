#include "stdafx.h"
#include "system_movement.h"

UpdateSystems::Movement::Movement() = default;

UpdateSystems::Movement::~Movement() = default;

void UpdateSystems::Movement::update()
{
	for (auto g : get_grouped_entities())
		for (auto &e : *g)
		{
			auto transform = &e->getComponent<Components::Transform>();

			transform->position.x += transform->velocity.x * transform->speed;
			transform->position.y += transform->velocity.y * transform->speed;
		}
}
