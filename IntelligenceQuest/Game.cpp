#include "stdafx.h"
#include <sstream>
#include <string>
#include <SDL_mixer.h>
#include <glm.hpp>
#include "component_collision.h"
#include "system_dynamic_renderer.h"
#include "system_static_renderer.h"
#include "system_controller.h"
#include "system_camera.h"
#include "system_movement.h"
#include "component_animation.h"
#include "system_animation.h"
Map* map;
Context context("map context");
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 2560, 2240 };
AssetManager* Game::assets = new AssetManager(&manager);

KeyboardHandler Game::keyboard_handler = KeyboardHandler();
//OpenGL context
SDL_GLContext gContext;

int Game::SCREEN_WIDTH;
int Game::SCREEN_HEIGHT;

bool Game::is_running = false;
auto& player(manager.add_entity());
auto& test(manager.add_entity());
auto& test2(manager.add_entity());
auto& label(manager.add_entity());

Game::Game()
	: window()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
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
		gContext = SDL_GL_CreateContext(window);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1)
			is_running = true;
	}

	assets->AddTexture("terrain", "tile_set_2.png");
	assets->AddTexture("player", "flesh_child_full.png");	
	assets->AddTexture("projectile", "rock.png");
	assets->AddTexture("textbox", "textbox.png");

	assets->AddFont("gilsans", "GIL_____.TTF", 18);

	map = new Map("terrain", 4, 32);

	map->LoadFullMap("testMap.xml");

	player.add_component<Components::Transform>(628, 564, 64, 64, 1);
	player.add_component<Components::Render>("player", new SDL_Rect{ 0,0,64,64 }, new SDL_Rect{0,0,64,64});
	player.add_component<Components::Collision>("player");
	player.add_component<Components::FrameAnimation>();
	player.add_group(groupPlayers);

	SDL_Color white = { 255, 255, 255, 255 };

	const auto daddysgroove = Mix_LoadMUS("daddysgroove.mp3");
	Mix_PlayMusic(daddysgroove, -1);

	//label.add_component<Components::UILabel>(10, 10, "TEST", "gilsans", white);
	//label.add_group(groupLabels::groupTextBoxes);

	auto dynamic_r = manager.add_render_system<RenderSystems::DynamicRenderer>();
	auto static_r = manager.add_render_system<RenderSystems::StaticRenderer>();

	auto anim_u = manager.add_update_system<UpdateSystems::Animation>();
	auto controller_u = manager.add_update_system<UpdateSystems::Controller>();
	auto move_u = manager.add_update_system<UpdateSystems::Movement>();
	auto camera_u = manager.add_update_system<UpdateSystems::Camera>(&player);

	anim_u->add_grouped_entities(Game::groupPlayers);

	dynamic_r->add_grouped_entities(Game::groupMap);
	dynamic_r->add_grouped_entities(Game::groupPlayers);
	//static_r->add_grouped_entities(Game::groupTextBoxes);

	controller_u->add_grouped_entities(Game::groupPlayers);
	move_u->add_grouped_entities(Game::groupPlayers);

}

void Game::handleEvents()
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
	manager.refresh(); 
	manager.update();
}



void Game::render()
{
	SDL_RenderClear(renderer);
	manager.render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
