#pragma once

#include "SDL.h"
#include <string>
#include "Game.h"

class KeyboardHandler
{
public:

	KeyboardHandler()
	{
	}

	bool check_key_event(SDL_Keycode key, SDL_EventType type)
	{
		return key_events[key] == type;
	}

	bool check_key_state(int keyCode) const
	{
		return (key_states[keyCode]);
	}

	const Uint8* key_states = SDL_GetKeyboardState(NULL);

	Uint32 key_events[];
private:
};
