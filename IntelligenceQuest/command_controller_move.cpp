#include "stdafx.h"
#include <sstream>
#include "component_movement.h"
#include "controller.h"
#include "command_controller_move.h"

#define ONE_OVER_SQRT_TWO 0.70710678118

ControllerCommands::Move::Move(Components::Movement * movement)
	: movement_(movement)
{}
ControllerCommands::Move::~Move() = default;

void ControllerCommands::Move::execute()
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

	movement_->velocity.x = x;
	movement_->velocity.y = y;
}
