#include "stdafx.h"
#include "controller.h"

int Controller::left = SDL_SCANCODE_LEFT; 
int Controller::right = SDL_SCANCODE_RIGHT;
int Controller::down = SDL_SCANCODE_DOWN;
int Controller::up = SDL_SCANCODE_UP; 
int Controller::action_1 = SDL_SCANCODE_Z;
int Controller::action_2 = SDL_SCANCODE_X;
int Controller::action_3 = SDL_SCANCODE_C;
int Controller::menu = SDL_SCANCODE_Q;

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


