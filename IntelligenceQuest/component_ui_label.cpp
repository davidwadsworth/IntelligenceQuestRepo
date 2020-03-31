#include "stdafx.h"
#include "component_ui_label.h"

Components::UILabel::UILabel(const int x, const int y, const std::string text, const std::string font, SDL_Color & color)
	: labelText(text), labelFont(font), textColor(color)
{
	position.x = x;
	position.y = y;

	set_label_text(labelText, labelFont);
}

Components::UILabel::~UILabel() = default;

void Components::UILabel::set_label_text(std::string text, const std::string font)
{
	SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->get_font(font), text.c_str(), textColor);
	labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
}


