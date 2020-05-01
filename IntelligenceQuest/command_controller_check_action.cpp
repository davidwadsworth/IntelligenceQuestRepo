#include "stdafx.h"
#include "command_controller_check_action.h"
#include "controller.h"

ControllerCommands::CheckAction::CheckAction()
	: is_pressed_(false)
{}
ControllerCommands::CheckAction::~CheckAction() = default;

void ControllerCommands::CheckAction::execute()
{
}
