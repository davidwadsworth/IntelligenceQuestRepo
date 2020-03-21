#pragma once

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "AssetManager.h"
#include "InputContext.h"
#include <SDL.h>
#include "KeyboardHandler.h"
#include <Box2D/Dynamics/b2World.h>

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {return is_running;}


	
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool is_running;
	static SDL_Rect camera;
	static AssetManager* assets;
	static int SCREEN_HEIGHT;
	static int SCREEN_WIDTH;
	static KeyboardHandler keyboard_handler;

	SDL_Window *window;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupControllers,
		groupTextBoxes
	};

private:

};
