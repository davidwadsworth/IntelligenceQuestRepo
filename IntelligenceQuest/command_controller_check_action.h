#pragma once
#include "command.h"

namespace ControllerCommands
{
	class CheckAction : public Command
	{
		bool is_pressed_;
	public:
		CheckAction();
		~CheckAction();

		void execute() override;
	};
}
