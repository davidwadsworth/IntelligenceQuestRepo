#include "stdafx.h"
#include "collision_world.h"

QuadTree * CollisionWorld::root_ = new QuadTree(glm::vec2(0,0), 2560, 2240 ); // TODO rethink this if nessasary
unruly<CollisionSubscriber*, max_subscriber> CollisionWorld::subscribers_;


CollisionSubscriber::CollisionSubscriber(Entity * entity)
	: entity_(entity)
{}

void CollisionSubscriber::check_in()
{
	if (active_)
		this->last_active_ = SDL_GetTicks();
	else
		CollisionWorld::subscribe(this);
}

std::vector<Entity*> CollisionSubscriber::retrieve()
{
	return CollisionWorld::retrieve(this);
}

std::vector<Entity*> CollisionWorld::retrieve(CollisionSubscriber * subscriber)
{
	return root_->retrieve(subscriber->entity_);
}

void CollisionWorld::insert(Entity * entity)
{
	root_->insert(entity);
}

void CollisionWorld::print()
{
	std::cout << *root_;
}

void CollisionWorld::refresh()
{
	auto i = 0;
	while (i < subscribers_.size)
	{
		if (SDL_GetTicks() - subscribers_[i]->last_active_ > max_inactive)
		{
			subscribers_[i]->active_ = false;
			subscribers_.remove(i);
		}
		else
			root_->refresh(subscribers_[i++]->entity_);
	}
}

void CollisionWorld::subscribe(CollisionSubscriber* subscriber)
{
	subscribers_.push_back(subscriber);
	subscriber->active_ = true;
	subscriber->last_active_ = SDL_GetTicks();
}


