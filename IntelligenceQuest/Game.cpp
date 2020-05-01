#include "stdafx.h"
#include <sstream>
#include <string>
#include <SDL_mixer.h>
#include "game_object_player.h"
#include "game_object_tile_map.h"

#define DEBUG true

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

GameObjects::Camera* Game::camera = nullptr;
AssetManager* Game::assets = new AssetManager();

KeyboardHandler Game::keyboard_handler = KeyboardHandler();

GameObjects::Player* player;
DataLoads::LTileMap* tile_map;

int Game::SCREEN_WIDTH;
int Game::SCREEN_HEIGHT;

float Game::delta_time;

bool Game::is_running = false;
Game::Game()
	: window()
{}

Game::~Game()
{}

void Game::init(const char *title, const int xpos, int ypos, int width, int height, bool fullscreen)
{
	
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags | SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1)
			is_running = true;
	}

	assets->add_texture("test_map", "assets/images/tile_set_2.png");
	assets->add_texture("player", "assets/images/flesh_child_full.png");	
	
	camera = new GameObjects::Camera(glm::vec2(0));

	tile_map = new DataLoads::LTileMap("test_map", &collision_tree, glm::vec2(), 3.0f, DEBUG);
	tile_map->load("assets/data/test_map2.xml");

	camera->boundary_width = tile_map->map_width * tile_map->scaled_size - Game::SCREEN_WIDTH;
	camera->boundary_height = tile_map->map_height * tile_map->scaled_size - Game::SCREEN_HEIGHT;

	player = new GameObjects::Player("player", collision_tree, glm::vec2(640, 640), 64, 64, 1.0f, 18);

	//const auto daddysgroove = Mix_LoadMUS("assets/audio/daddysgroove.mp3");
	//Mix_PlayMusic(daddysgroove, -1);

	Manager::add_group_to_system(group_map);
	Manager::add_group_to_system(group_colliders);
	Manager::add_group_to_system(group_players);
	Manager::add_group_to_system(group_camera);
}

void Game::handle_events()
{
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;

	default:
		break;
	}
}

void Game::update() 
{
	Manager::refresh();
	Manager::update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Manager::render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	collision_tree->delete_map();

	delete collision_tree;
	collision_tree = nullptr;
	delete assets;
	assets = nullptr;
	delete tile_map;
	tile_map = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
