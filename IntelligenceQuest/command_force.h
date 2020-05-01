#pragma once
#include "component_transform.h"
#include "command.h"
#include "component_physics.h"

namespace Commands
{
	class Force : public Command
	{
		Components::Physics* physics_;
		Components::Transform* transform_;
	public:
		Force(Components::Physics* physics, Components::Transform *transform);
		~Force();

		void execute() override;
	};
}
