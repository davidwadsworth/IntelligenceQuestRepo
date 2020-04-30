#include "stdafx.h"
#include "collider.h"

glm::vec2 Collider::triple_product(glm::vec2 a, glm::vec2 b, glm::vec2 c)
{
	auto a3 = glm::vec3(a, 0);
	auto b3 = glm::vec3(b, 0);
	auto c3 = glm::vec3(c, 0);

	return glm::vec2(glm::cross(glm::cross(a3, b3), c3));
}

Collider::Collider(glm::vec2 * position)
	: position_(position)
{}

Collider::Collider(glm::vec2 * position, glm::vec2 offset)
	: position_(position), offset_(offset)
{}

Collider::~Collider() = default;

glm::vec2 Collider::get_center()
{
	return *position_ + offset_;
}

glm::vec2 Collider::get_position()
{
	return *position_;
}

glm::vec2 Collider::get_offset() const
{
	return offset_;
}

void Collider::set_offset(glm::vec2 offset)
{
	offset_ = offset;
}

bool Collider::collide(Collider * col)
{
	auto i = 0;
	
	glm::vec2 direction, a, b, c;

	while (true)
	{
		switch (i)
		{
		case 0:
			direction = this->get_center() - col->get_center();
			break;
		case 1:
			direction *= -1;
			break;
		case 2:
			b = vertices_[1];
			c = vertices_[0];

			auto cb = b - c;
			auto c0 = -c;

			direction = triple_product(cb, c0, cb);
			break;
		case 3:
			a = vertices_[2];
			b = vertices_[1];
			c = vertices_[0];

			auto a0 = -a;
			auto ab = b - a;
			auto ac = c - a;

			auto ab_perpindicular = triple_product(ac, ab, ab);
			auto ac_perpindicular = triple_product(ab, ac, ac);

			if (glm::dot(ab_perpindicular, a0) > 0)
			{
				vertices_[0] = vertices_[1];
				vertices_[1] = vertices_[2];
				i--;
				direction = ab_perpindicular;
			}
			else if (glm::dot(ac_perpindicular, a0) > 0)
			{
				vertices_[2] = vertices_[1];
				i--;
				direction = ac_perpindicular;
			}
			else
				return true;
			break;
		default:
			SDL_Log("Cant have a simplex with more than 3 vertices!");
			return false;
			break;
		}

		vertices_[i] = this->support(direction) - col->support(-direction);
		if (glm::dot(vertices_[i++], direction) < 0)
			return false;
	}
}


