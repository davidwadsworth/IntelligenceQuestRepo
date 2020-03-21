#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace Components
{
	class UILabel : public Component
	{
	public:

		UILabel(const int x, const int y, const std::string text, const std::string font, SDL_Color& color);
		~UILabel();
		void set_label_text(std::string text, const std::string font);
	private:
		SDL_Rect position;
		std::string labelText;
		std::string labelFont;
		SDL_Color textColor;
		SDL_Texture* labelTexture;
	};
}