#pragma once
#include "command.h"
#include "component_movement.h"

namespace Commands
{
	class PlayerMove : public Command
	{
		Components::Movement * movement_;
		glm::vec2 force_;
	public:
		PlayerMove(Components::Movement * movement, glm::vec2 force);
		~PlayerMove();

		void execute() override;
	};
}
