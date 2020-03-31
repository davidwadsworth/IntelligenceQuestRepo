#include "stdafx.h"
#include <sstream>
#include "component_movement.h"
#include "controller.h"
#include "command_controller_move.h"

Commands::PlayerMove::PlayerMove(Components::Movement * movement)
	: movement_(movement)
{}
Commands::PlayerMove::~PlayerMove() = default;

void Commands::PlayerMove::execute()
{
	float x = 0, y = 0;

	if (Game::keyboard_handler.checkKeyState(Controller::right)) x++;
	if (Game::keyboard_handler.checkKeyState(Controller::left)) x--;
	if (Game::keyboard_handler.checkKeyState(Controller::down)) y++;
	if (Game::keyboard_handler.checkKeyState(Controller::up)) y--;

	if (x != 0 && y != 0)
	{
		const auto diagonal_vel = (movement_->speed - static_cast<int>(movement_->speed) / 3) / movement_->speed;
 		
		x *= diagonal_vel;
		y *= diagonal_vel;
	}

	movement_->velocity.x = x;
	movement_->velocity.y = y;
}
