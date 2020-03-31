#pragma once
#include "command.h"
#include "component_movement.h"

namespace Commands
{
	class PlayerMove : public Command
	{
		Components::Movement * movement_;
	public:
		PlayerMove(Components::Movement * movement);
		~PlayerMove();

		void execute() override;
	};
}
