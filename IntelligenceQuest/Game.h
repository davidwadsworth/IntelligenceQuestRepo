#pragma once

#include <SDL.h>
#include "keyboard_handler.h"
#include "asset_manager.h"
#include "quad_tree.h"
#include "game_object_camera.h"

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handle_events();
	void update();
	void render();
	void clean();

	static bool running() {return is_running;}

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool is_running;
	static GameObjects::Camera* camera;
	static AssetManager* assets;
	static int SCREEN_HEIGHT;
	static int SCREEN_WIDTH;
	static KeyboardHandler keyboard_handler;
	static float delta_time;

	// TEMP VARIABLES until game states are added
	QuadTree* collision_tree;
	//QuadTree trigger_tree;

	SDL_Window *window;

	enum group_labels : std::size_t
	{
		group_map,
		group_players,
		group_colliders,
		group_projectiles,
		group_controllers,
		group_text_boxes,
		group_camera
	};

private:

};
