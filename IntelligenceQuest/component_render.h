#pragma once

#include "SDL.h"
#include "AssetManager.h"


namespace Components
{
	class Render : public Component
	{
	public:
		SDL_Texture *texture;
		SDL_Rect *src, *dest;
		SDL_Point* rotation_point;
		float rotation;
		SDL_RendererFlip flip;

		explicit Render(std::string id, SDL_Rect* dest);
		Render(std::string id, SDL_Rect* dest, SDL_Rect* src);
		Render(std::string id, SDL_Rect* dest, SDL_Rect* src, SDL_Point * rot_point, double rot, SDL_RendererFlip flip);
		~Render();

		void set_tex(std::string id);
	};
}