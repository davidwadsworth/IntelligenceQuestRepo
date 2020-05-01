#pragma once
#include "command.h"
#include "component_transform.h"

namespace Commands
{
	class CameraFollow : public Command
	{
		Components::Transform * follow_transform_;
	public:
		CameraFollow(Components::Transform * follow_transform);
		~CameraFollow();

		void execute() override;
	};
}
