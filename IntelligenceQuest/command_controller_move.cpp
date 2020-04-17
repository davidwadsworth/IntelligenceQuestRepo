#include "stdafx.h"
#include <sstream>
#include "component_movement.h"
#include "controller.h"
#include "command_controller_move.h"

#define ONE_OVER_SQRT_TWO 0.70710678118

Commands::PlayerMove::PlayerMove(Components::Movement * movement, glm::vec2 force)
	: movement_(movement), force_(force)
{}
Commands::PlayerMove::~PlayerMove() = default;

void Commands::PlayerMove::execute()
{
	float x = 0, y = 0;

	if (Game::keyboard_handler.check_key_state(Controller::right)) x++;
	if (Game::keyboard_handler.check_key_state(Controller::left)) x--;
	if (Game::keyboard_handler.check_key_state(Controller::down)) y++;
	if (Game::keyboard_handler.check_key_state(Controller::up)) y--;

	if (x != 0 && y != 0)
	{
		//const auto diagonal_vel = (adjusted_speed - static_cast<int>(adjusted_speed) / 3) / adjusted_speed;
		
		//std::cout << "diagonal: " << Game::camera.x << ", " << Game::camera.y << std::endl;

		x *= ONE_OVER_SQRT_TWO;
		y *= ONE_OVER_SQRT_TWO;
	}
	//else
		//std::cout << "cardigan: " << Game::camera.x << ", " << Game::camera.y << std::endl;

	movement_->force.x += x * force_.x;
	movement_->force.y += y * force_.y;
}
