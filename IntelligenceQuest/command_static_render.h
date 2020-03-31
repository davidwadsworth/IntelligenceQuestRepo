#pragma once
#include "command.h"

namespace Commands
{
	class StaticRender : public Command
	{
		Components::Render * render_;
	public:
		StaticRender(Components::Render * render);
		~StaticRender();

		void execute() override;
	};
}
