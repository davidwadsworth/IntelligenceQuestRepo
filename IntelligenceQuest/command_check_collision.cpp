#include "stdafx.h"
#include "command_check_collision.h"
#include "collision_world.h"

Commands::CheckCollision::CheckCollision(Entity * entity, Components::Collision* collider, Components::Movement * movement, Components::Transform* transform)
	: CollisionSubscriber(entity), collider_(collider), movement_(movement), transform_(transform)
{}

Commands::CheckCollision::~CheckCollision() = default;

void Commands::CheckCollision::execute()
{
	this->check_in();

	auto entities_ = this->retrieve();
	for (auto e : entities_)
	{
		auto collider_c = &e->get_component<Components::Collision>();
		if (collider_c != collider_ && collider_->get_collider()->collide(collider_c->get_collider()))
		{
			auto piercing_vec = collider_->get_collider()->intersecting_vector(collider_c->get_collider());
			//transform_->position = transform_->prev_position;

			std::cout << piercing_vec.x << ", " << piercing_vec.y << std::endl;

			transform_->position += (transform_->prev_position - transform_->position) + piercing_vec;
			//movement_->force += piercing_vec;
		}
	}
}
