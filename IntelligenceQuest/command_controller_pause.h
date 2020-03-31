#pragma once
#include "command.h"

namespace Commands
{
	class Pause : public Command
	{
	public:
		Pause();
		~Pause();

		void execute() override;
	};
}
