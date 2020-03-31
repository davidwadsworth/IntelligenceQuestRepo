#include "stdafx.h"
#include "component_text_box.h"
#include "asset_manager.h"


AssetManager::AssetManager() = default;

AssetManager::~AssetManager()
{}

void AssetManager::add_texture(std::string id, const char* path)
{
	textures_.emplace(id, TextureManager::load_texture(path));
}

SDL_Texture* AssetManager::get_texture(std::string id)
{
	return textures_[id];
}

void AssetManager::add_font(std::string id, std::string path, int font_size)
{
	fonts_.emplace(id, TTF_OpenFont(path.c_str(), font_size));
}

TTF_Font * AssetManager::get_font(std::string id)
{
	return fonts_[id];
}

