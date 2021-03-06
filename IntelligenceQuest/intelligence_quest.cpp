// intelligence_quest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define FRAME_RATE 1.0f / 60.0f

Game *game = nullptr;

int main(int argc, char *argv[])
{
	const int fps = 60;
	const int frame_delay = 1000 / fps;

	game = new Game();
	game->init("IntelligenceQuest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	Game::delta_time = 0.0f;
	auto last_frame = 0.0f;

	while (game->running())
	{
		float current_frame = static_cast<float>(SDL_GetTicks());
		Game::delta_time = (current_frame - last_frame) * FRAME_RATE;
		last_frame = current_frame;

		game->handle_events();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}

