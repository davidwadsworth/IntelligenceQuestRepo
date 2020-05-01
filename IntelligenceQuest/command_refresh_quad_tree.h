#pragma once
#include "command.h"
#include "quad_tree.h"

namespace Commands
{
	class RefreshQuadTree : public Command
	{
		Entity* entity_;
		QuadTree* tree_;
	public:
		RefreshQuadTree(Entity * entity, QuadTree* tree);
		~RefreshQuadTree();
		void execute() override;
	};
}

