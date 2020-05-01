#pragma once
#include "game_object.h"

namespace GameObjects
{
	class Camera : public GameObject
	{
	public:
		Components::Transform* transform;
		Entity* entity;
		int boundary_width, boundary_height;
		Camera(glm::vec2 position);
		~Camera();
	};
}