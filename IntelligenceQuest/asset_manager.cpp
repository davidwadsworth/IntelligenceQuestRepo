#include "stdafx.h"
#include "component_text_box.h"
#include "asset_manager.h"


AssetManager::AssetManager() = default;

AssetManager::~AssetManager()
{
	textures_.clear();
	fonts_.clear();
}

void AssetManager::add_texture(std::string id, const char* path)
{
	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> u_ptr(TextureManager::load_texture(path), SDL_DestroyTexture);
	textures_.emplace(id, std::move(u_ptr));
}

SDL_Texture* AssetManager::get_texture(std::string id)
{
	return textures_[id].get();
}

void AssetManager::add_font(std::string id, std::string path, int font_size)
{
	std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> u_ptr(TTF_OpenFont(path.c_str(), font_size), TTF_CloseFont);
	fonts_.emplace(id, std::move(u_ptr));
}

TTF_Font * AssetManager::get_font(std::string id)
{
	return fonts_[id].get();
}

