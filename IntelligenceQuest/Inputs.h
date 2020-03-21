#pragma once

#include <string>
#include "SDL.h"
#include <list>

class Action {
};

class State
{
public:

	State(const char* nm, std::list<SDL_Keycode> kP, std::list<SDL_Keycode> kE, SDL_EventType eT, glm::vec2 vel, const char* anim)
		: name(nm), keyPresses(kP), keyExclusions(kE), eventType(eT), velocity(vel), animation(anim)
	{}

	SDL_EventType eventType;
	glm::vec2 velocity;
	const char* name;
	std::list<SDL_Keycode> keyPresses;
	std::list<SDL_Keycode> keyExclusions;
	const char* animation;
private:

};
class Range {
};
