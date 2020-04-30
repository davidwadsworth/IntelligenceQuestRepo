#include "stdafx.h"
#include <sstream>
#include "component_movement.h"
#include "controller.h"
#include "command_controller_move.h"

constexpr auto ONE_OVER_SQRT_TWO = 0.70710678118f;

ControllerCommands::Move::Move(Components::Movement * movement, Components::Physics* physics)
	: movement_(movement), physics_(physics)
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
		x *= ONE_OVER_SQRT_TWO;
		y *= ONE_OVER_SQRT_TWO;
	}

	physics_->direction = glm::vec2(x, y);
	physics_->force += movement_->speed;
}
