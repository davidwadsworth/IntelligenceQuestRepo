#pragma once
#include "collider_circle.h"
#include "unruly.h"
#include "quad_tree.h"

//TODO remove
constexpr std::size_t max_subscriber = 32;
constexpr std::size_t max_buffer = 64;
constexpr std::size_t max_inactive = 5000; // if a subscriber is inactive for 5 seconds off screen it no longer receives collision checks and must be re-queued

//TODO remove
class CollisionSubscriber : public Command
{
	Uint32 last_active_;
	bool active_;
	Entity * entity_;
	friend class CollisionWorld;
public:
	CollisionSubscriber(Entity * entity);

	void check_in();
	std::vector<Entity*> retrieve();
};


//TODO remove static
class CollisionWorld
{
	static QuadTree* root_;
	static unruly<CollisionSubscriber*, max_subscriber> subscribers_;
	CollisionWorld() = default;
public:	
	//TODO replace subscriber with entity
	static std::vector<Entity*> retrieve(CollisionSubscriber* subscriber);
	static void insert(Entity * entity);
	static void print();
	static void refresh();
	//TODO remove
	static void subscribe(CollisionSubscriber* subscriber);
};
