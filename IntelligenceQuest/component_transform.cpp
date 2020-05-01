#include "stdafx.h"
#include "component_transform.h"

Components::Transform::Transform()
{
	position.x = 0.0f;
	position.y = 0.0f;
}

Components::Transform::Transform(int sc)
{
	position.x = 400;
	position.y = 320;
	scale = sc;
}

Components::Transform::Transform(float x, float y)
{
	position.x = x;
	position.y = y;
}

Components::Transform::Transform(glm::vec2 position, int h, int w)
	: position(position), prev_position(), height(h), width(w), scale(1)
{}

Components::Transform::Transform(float x, float y, int h, int w, int sc)
{
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	scale = sc;
}
