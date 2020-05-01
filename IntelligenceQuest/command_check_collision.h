#pragma once
#include "component_physics.h"

namespace Commands
{
	class CheckCollision : public Command
	{
		Components::Collision* collider_;
		Components::Physics* physics_;
		Components::Transform* transform_;
		Entity* entity_;

	public:
		CheckCollision(Entity * entity, Components::Collision* collider, Components::Physics* movement, Components::Transform* transform);
		~CheckCollision();

		void execute() override;
	};
}
