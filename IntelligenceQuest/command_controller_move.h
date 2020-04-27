#pragma once
#include "command.h"
#include "component_movement.h"

namespace ControllerCommands
{
	class Move : public Command
	{
		Components::Movement * movement_;
	public:
		Move(Components::Movement * movement);
		~Move();

		void execute() override;
	};
}
