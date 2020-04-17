#pragma once
#include "component_movement.h"
#include "collision_world.h"

namespace Commands
{
	class CheckCollision : public CollisionSubscriber
	{
		Components::Collision* collider_;
		Components::Movement* movement_;
		Components::Transform* transform_;

	public:
		CheckCollision(Entity * entity, Components::Collision* collider, Components::Movement* movement, Components::Transform* transform);
		~CheckCollision();

		void execute() override;
	};
}
