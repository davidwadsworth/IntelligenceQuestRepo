#pragma once

#include <map>
#include <string>
#include "SDL_ttf.h"
#include <functional>

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
	std::map<std::string, std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>> textures_;
	std::map<std::string, std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>>> fonts_;
};
