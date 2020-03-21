#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Game.h"

namespace Components
{
	class TextBoxComponent : public Component
	{
	public:
		SDL_Texture * texture;
		SDL_Rect srcRect, destRect;
		glm::vec2 position;

		TextBoxComponent() = default;
		TextBoxComponent(int srcX, int srcY, int xpos, int ypos, int size, int wscale, int hscale, int rots, SDL_RendererFlip flp, std::string id);
		~TextBoxComponent();
	private:
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		int rotations = 0;
	};
}