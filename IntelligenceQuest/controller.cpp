#include "stdafx.h"
#include "controller.h"

int Controller::left = 80;
int Controller::right = 79;
int Controller::down = 81;
int Controller::up = 82;
int Controller::action_1 = 29;
int Controller::action_2 = 30;
int Controller::action_3 = 31;
int Controller::menu = 27;

void Controller::set_key(const int key, const std::string key_id)
{
	if (key_id == "left")
		left = key;
	else if (key_id == "right")
		right = key;
	else if (key_id == "down")
		down = key;
	else if (key_id == "up")
		up = key;
	else if (key_id == "action_1")
		action_1 = key;
	else if (key_id == "action_2")
		action_2 = key;
	else if (key_id == "action_3")
		action_3 = key;
	else
		menu = key;
}


