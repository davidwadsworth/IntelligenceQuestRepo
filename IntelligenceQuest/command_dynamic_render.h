#pragma once
#include "command.h"

namespace Commands
{
	class DynamicRender : public Command
	{
		Components::Render * render_;
		Components::Transform * transform_;
	public:
		DynamicRender(Components::Render* render, Components::Transform * transform);
		~DynamicRender();

		void execute() override;
	};
}
