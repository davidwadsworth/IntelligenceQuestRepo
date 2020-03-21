#pragma once
#include "ECS.h"

namespace RenderSystems
{
	class StaticRenderer : public System
	{
	public:
		StaticRenderer();
		~StaticRenderer();
		void update() override;
	};
}