#pragma once
#include "ECS.h"

namespace UpdateSystems
{
	class Camera : public System
	{
		Entity * target_;
	public:
		Camera(Entity * target);
		~Camera();

		void change_target(Entity * n_target);
		void update() override;
	};
}
