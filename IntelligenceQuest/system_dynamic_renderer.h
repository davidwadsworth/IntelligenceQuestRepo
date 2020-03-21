#pragma once
#include "ECS.h"

namespace RenderSystems
{
	class DynamicRenderer : public System
	{
	public:
		DynamicRenderer();
		~DynamicRenderer();
		void update() override;
	};
}
