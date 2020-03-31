#pragma once
#include "component_movement.h"
#include "command.h"


namespace Commands
{
	class Movement : public Command
	{
		Components::Movement * movement_;
		Components::Transform * transform_;
	public:
		Movement(Components::Movement* movement, Components::Transform *transform);
		~Movement();

		void execute() override;
	};
}
