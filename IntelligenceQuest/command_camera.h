#pragma once
#include "command.h"

namespace Commands
{
	class Camera : public Command
	{
		Components::Transform * transform_;
	public:
		Camera(Components::Transform * transform);
		~Camera();

		void execute() override;
	};
}
