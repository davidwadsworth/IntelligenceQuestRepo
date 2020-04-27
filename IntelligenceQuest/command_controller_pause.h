#pragma once
#include "command.h"

namespace ControllerCommands
{
	class Pause : public Command
	{
	public:
		Pause();
		~Pause();

		void execute() override;
	};
}
