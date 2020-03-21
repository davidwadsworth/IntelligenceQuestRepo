#include "stdafx.h"
#include "game.h"
#include "system_camera.h"

UpdateSystems::Camera::Camera(Entity* target)
	: target_(target)
{}
UpdateSystems::Camera::~Camera() = default;

void UpdateSystems::Camera::change_target(Entity * n_target)
{
	target_ = n_target;
}

void UpdateSystems::Camera::update()
{
	const auto transform = target_->getComponent<Components::Transform>();

	Game::camera.x = transform.position.x - (Game::SCREEN_WIDTH / 2);
	Game::camera.y = transform.position.y - (Game::SCREEN_HEIGHT / 2);

	if (Game::camera.x < 0)
		Game::camera.x = 0;
	if (Game::camera.y < 0)
		Game::camera.y = 0;
	if (Game::camera.x > Game::camera.w)
		Game::camera.x = Game::camera.w;
	if (Game::camera.y > Game::camera.h)
		Game::camera.y = Game::camera.h;

}
