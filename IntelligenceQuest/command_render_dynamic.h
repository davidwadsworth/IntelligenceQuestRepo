#pragma once
#include "command.h"

namespace RenderCommands
{
	class Dynamic : public Command
	{
		Components::Render * render_;
		Components::Transform * transform_;
	public:
		Dynamic(Components::Render* render, Components::Transform * transform);
		~Dynamic();

		void execute() override;
	};
}
