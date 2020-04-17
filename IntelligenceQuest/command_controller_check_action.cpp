#include "stdafx.h"
#include "command_controller_check_action.h"
#include "controller.h"
#include "collision_world.h"

Commands::CheckAction::CheckAction()
	: is_pressed_(false)
{}
Commands::CheckAction::~CheckAction() = default;

void Commands::CheckAction::execute()
{
	if (Game::keyboard_handler.check_key_state(Controller::action_1))
	{
		if (!is_pressed_)
		{
			is_pressed_ = true;
			CollisionWorld::print();
		}
	}
	else
		is_pressed_ = false;
	/*TODO create list of Triggered entities for this entity to check if the entities action falls in collision with*/ 
}
