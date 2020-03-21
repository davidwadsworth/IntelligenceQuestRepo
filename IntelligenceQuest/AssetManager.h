#pragma once

#include <map>
#include <string>
#include "texture_manager.h"
#include "ECS.h"
#include "SDL_ttf.h"
#include <vec2.hpp>


class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//gameObjects

	void CreateProjectile(glm::vec2 pos, glm::vec2 vel, int range, int speed, std::string id);

	void CreateBox(int x, int y, int width, int height, int offsetX, int offsetY, int scale, std::string id);

	void CreateTextBox(int x, int y, int width, int height, int offsetX, int offsetY, int scale, std::string text);

	void CreateTextBox(int x, int y, TTF_Font* font, std::string text);

	void CreateMenu(int x, int y);

	//Texture management
	void AddTexture(std::string id, const char* path);

	SDL_Texture * GetTexture(std::string id);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

private:
	
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};
