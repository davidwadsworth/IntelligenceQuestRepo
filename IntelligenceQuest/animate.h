#pragma once
#include <SDL.h>


struct Animate
{};


struct FrameAnimate : Animate
{
	int index;
	int frames;
	int speed;
	int rotations;
	SDL_RendererFlip flip;

	FrameAnimate() = default;
	FrameAnimate(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
		rotations = 0;
		flip = SDL_FLIP_NONE;
	}

	FrameAnimate(int i, int f, int s, int rots, SDL_RendererFlip flp)
	{
		index = i;
		frames = f;
		speed = s;
		rotations = rots;
		flip = flp;
	}

};