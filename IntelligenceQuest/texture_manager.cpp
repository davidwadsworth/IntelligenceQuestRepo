#include "stdafx.h"
#include "texture_manager.h"


SDL_Texture* TextureManager::load_texture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::draw(SDL_Texture * tex, SDL_Rect* src, SDL_Rect* dest, double rots, SDL_Point* rotation_point,  SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, src, dest, rots, rotation_point, flip);
}

void TextureManager::draw(SDL_Texture * tex, SDL_Rect* src, SDL_Rect* dest)
{
	SDL_RenderCopy(Game::renderer, tex, src, dest);
}
