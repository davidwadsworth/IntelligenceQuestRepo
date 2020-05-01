#pragma once
#include "stdafx.h"
#include "game_object_camera.h"
#include "command_camera_follow.h"

GameObjects::Camera::Camera(glm::vec2 position)
{
	entity = &Manager::add_entity();
	transform = &entity->add_component<Components::Transform>(position, Game::SCREEN_HEIGHT, Game::SCREEN_WIDTH);
	this->add_group(Game::group_camera);
}
GameObjects::Camera::~Camera() = default;
