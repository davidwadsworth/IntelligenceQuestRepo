#pragma once
#include "command.h"
#include "component_movement.h"
#include "component_physics.h"

namespace ControllerCommands
{
	class Move : public Command
	{
		Components::Movement * movement_;
		Components::Physics * physics_;
	public:
		Move(Components::Movement * movement, Components::Physics* physics);
		~Move();

		void execute() override;
	};
}
