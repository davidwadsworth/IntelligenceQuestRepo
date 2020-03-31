#include "stdafx.h"
#include "component_text_box.h"

Components::TextBoxComponent::~TextBoxComponent()
{
	SDL_DestroyTexture(texture);
}

Components::TextBoxComponent::TextBoxComponent(int srcX, int srcY, int xpos, int ypos, int size, int wscale, int hscale, int rots, SDL_RendererFlip flp, std::string id)
{
	flip = flp;
	rotations = rots;
	texture = Game::assets->get_texture(id);

	position.x = xpos;
	position.y = ypos;

	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = srcRect.h = size;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = size * wscale;
	destRect.h = size * hscale;
}
