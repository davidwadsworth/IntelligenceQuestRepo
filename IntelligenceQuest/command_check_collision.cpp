#include "stdafx.h"
#include "command_check_collision.h"
#include "collision_world.h"
#include "sorting.h"

Commands::CheckCollision::CheckCollision(Entity * entity, Components::Collision* collider, Components::Movement * movement, Components::Transform* transform)
	: CollisionSubscriber(entity), collider_(collider), movement_(movement), transform_(transform)
{}

Commands::CheckCollision::~CheckCollision() = default;

void Commands::CheckCollision::execute()
{
	this->check_in();

	auto entities = this->retrieve();

	auto colliding_entities = std::vector<Collider *>();

	auto col_a = collider_->get_collider();

	for (auto e : entities)
	{
		auto col_b = e->get_component<Components::Collision>().get_collider();

		if (col_a != col_b && col_a->collide(col_b))
			colliding_entities.push_back(col_b);
	}

	if (colliding_entities.size() > 1)
		Sorts::sort_colliders(colliding_entities, col_a);

	for (auto col_b : colliding_entities)
	{
		auto piercing_vec = col_b->find_perpendicular_line(col_a, transform_->prev_position + col_a->get_offset());
		transform_->position += piercing_vec * glm::abs(transform_->prev_position - transform_->position); // piercing vec * velocity and speed of the previous move
	}

}
