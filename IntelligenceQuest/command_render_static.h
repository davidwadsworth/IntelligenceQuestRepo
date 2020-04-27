#pragma once
#include "command.h"

namespace RenderCommands
{
	class Static : public Command
	{
		Components::Render * render_;
	public:
		Static(Components::Render * render);
		~Static();

		void execute() override;
	};
}
