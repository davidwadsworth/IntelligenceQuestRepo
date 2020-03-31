// intelligence_quest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	const int fps = 60;
	const int frame_delay = 1000 / fps;

	game = new Game();
	game->init("IntelligenceQuest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);


	while (game->running())
	{
		const Uint32 frame_start = SDL_GetTicks();

		game->handle_events();
		game->update();
		game->render();

		const int frame_time = SDL_GetTicks() - frame_start;

		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);
		}
	}

	game->clean();
	return 0;
}

