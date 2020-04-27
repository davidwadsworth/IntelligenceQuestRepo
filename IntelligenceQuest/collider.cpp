#include "stdafx.h"
#include "collider.h"

glm::vec2 Collider::triple_product(glm::vec2 a, glm::vec2 b, glm::vec2 c)
{
	auto a3 = glm::vec3(a, 0);
	auto b3 = glm::vec3(b, 0);
	auto c3 = glm::vec3(c, 0);

	return glm::vec2(glm::cross(glm::cross(a3, b3), c3));
}

Collider::Edge Collider::find_closest_edge(bool clockwise)
{
	auto closest_distance = std::numeric_limits<float>::infinity();
	auto closest_normal = glm::vec2();
	auto closest_index = 0;

	auto line = glm::vec2();

	for (auto i = 0; i < vertices_.size(); i++)
	{
		auto j = i + 1;
		if (j >= vertices_.size()) j = 0;

		// change this to v[j] - v[i] if not working he said that but wrote this
		line = vertices_[i] - vertices_[j];

		auto norm = clockwise ? glm::vec2(line.y, -line.x) : glm::vec2(-line.y, line.x);

		norm = glm::normalize(norm);

		auto dist = glm::dot(norm, vertices_[i]);
		if (dist < closest_distance)
		{
			closest_distance = dist;
			closest_normal = norm;
			closest_index = j;
		}
	}

	return Edge{closest_distance, closest_normal, closest_index};
}

Collider::Collider(glm::vec2 * position, glm::vec2 offset)
	: position_(position), offset_(offset)
{}

Collider::~Collider() = default;

glm::vec2 Collider::get_center()
{
	return *position_ + offset_;
}

glm::vec2 Collider::get_offset() const
{
	return offset_;
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

glm::vec2 Collider::intersecting_vector(Collider * col)
{
	auto e0 = (vertices_[1].x - vertices_[0].x) * (vertices_[1].y + vertices_[0].y);
	auto e1 = (vertices_[2].x - vertices_[1].x) * (vertices_[2].y + vertices_[1].y);
	auto e2 = (vertices_[0].x - vertices_[2].x) * (vertices_[0].y + vertices_[2].y);

	auto clockwise = (e0 + e1 + e2) >= 0;
	auto intersection = glm::vec2();
	for (auto i = 0; i < MAX_INTERSECTING; i++)
	{
		auto edge = find_closest_edge(clockwise);
		auto sup = support(edge.normal);
		auto dist = glm::dot(sup, edge.normal);

		intersection = edge.normal;
		intersection *= dist;

		if (abs(dist - edge.distance) <= FLT_EPSILON)
			return intersection;
		else
			vertices_[edge.index] = sup;
	}
	return intersection;
}

