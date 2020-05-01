#include "stdafx.h"
#include "command_refresh_quad_tree.h"

Commands::RefreshQuadTree::RefreshQuadTree(Entity * entity, QuadTree * tree)
	: entity_(entity), tree_(tree)
{}

Commands::RefreshQuadTree::~RefreshQuadTree() = default;

void Commands::RefreshQuadTree::execute()
{
	tree_->refresh(entity_);
}
