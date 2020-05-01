#include "stdafx.h"
#include "command_camera_follow.h"


Commands::CameraFollow::CameraFollow(Components::Transform * follow_transform)
	: follow_transform_(follow_transform)
{}

Commands::CameraFollow::~CameraFollow() = default;

void Commands::CameraFollow::execute()
{
	auto& camera_pos = Game::camera->transform->position;

	camera_pos.x = follow_transform_->position.x - static_cast<float>(Game::camera->transform->width / 2);
	camera_pos.y = follow_transform_->position.y - static_cast<float>(Game::camera->transform->height / 2);

	if (camera_pos.x < 0)
		camera_pos.x = 0;
	if (camera_pos.y < 0)
		camera_pos.y = 0;
	if (camera_pos.x > Game::camera->boundary_width)
		camera_pos.x = Game::camera->boundary_width;
	if (camera_pos.y > Game::camera->boundary_height)
		camera_pos.y = Game::camera->boundary_height;
}

