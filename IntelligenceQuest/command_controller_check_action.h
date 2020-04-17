#pragma once
#include "command.h"

namespace Commands
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
