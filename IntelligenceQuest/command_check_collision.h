#pragma once
#include "collision_world.h"
#include "component_physics.h"

namespace Commands
{
	class CheckCollision : public CollisionSubscriber
	{
		Components::Collision* collider_;
		Components::Physics* physics_;
		Components::Transform* transform_;

	public:
		CheckCollision(Entity * entity, Components::Collision* collider, Components::Physics* movement, Components::Transform* transform);
		~CheckCollision();

		void execute() override;
	};
}
