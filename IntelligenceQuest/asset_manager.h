#pragma once

#include <map>
#include <string>
#include "SDL_ttf.h"


class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	//Texture management
	void add_texture(std::string id, const char* path);

	SDL_Texture * get_texture(std::string id);

	void add_font(std::string id, std::string path, int font_size);
	TTF_Font* get_font(std::string id);

private:
	std::map<std::string, SDL_Texture*> textures_;
	std::map<std::string, TTF_Font*> fonts_;
};
