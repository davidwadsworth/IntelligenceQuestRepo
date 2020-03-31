#include "stdafx.h"
#include "command_camera.h"


Commands::Camera::Camera(Components::Transform * transform)
	: transform_(transform)
{}

Commands::Camera::~Camera() = default;

void Commands::Camera::execute()
{
	Game::camera.x = transform_->position.x - static_cast<float>(Game::SCREEN_WIDTH / 2);
	Game::camera.y = transform_->position.y - static_cast<float>(Game::SCREEN_HEIGHT / 2);

	if (Game::camera.x < 0)
		Game::camera.x = 0;
	if (Game::camera.y < 0)
		Game::camera.y = 0;
	if (Game::camera.x > Game::camera.w)
		Game::camera.x = Game::camera.w;
	if (Game::camera.y > Game::camera.h)
		Game::camera.y = Game::camera.h;
}

