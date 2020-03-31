#pragma once
#include "command.h"

namespace Commands
{
	class CheckAction : public Command
	{
	public:
		CheckAction();
		~CheckAction();

		void execute() override;
	};
}
