#pragma once

#include "Game.h"

class TextureManager {

public: 
	static SDL_Texture* load_texture(const char* filename);
	static void draw(SDL_Texture* tex, SDL_Rect *src, SDL_Rect* dest, double rots, SDL_Point * rotation_point, SDL_RendererFlip flip);
	static void draw(SDL_Texture* tex, SDL_Rect *src, SDL_Rect* dest);
};