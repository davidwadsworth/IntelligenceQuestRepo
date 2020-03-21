#include "stdafx.h"
#include "component_text_box.h"


AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

//TODO move these abominations
void AssetManager::CreateProjectile(glm::vec2 pos, glm::vec2 vel, int range, int speed, std::string id)
{
	auto& projectile(manager->add_entity());
	projectile.add_component<Components::Transform>(pos.x, pos.y, 32, 32, 1);
	projectile.add_component<Components::Render>(id, nullptr);
	//projectile.add_component<Components::>(range, speed, vel);
	//projectile.add_component<ColliderComponent>("projectile");
	projectile.add_group(Game::groupProjectiles);
}

//TODO move these abominations
void AssetManager::CreateBox(int x, int y, int width, int height, int offsetX, int offsetY, int scale, std::string id)
{
	int tileSize = 10;
	int scaledSize = tileSize * scale;
	int boxW = scaledSize * width / 2;
	int boxH = scaledSize * height / 2;
	int leftX = x - boxW - offsetX;
	int topY = y - boxH - offsetY;
	int rightX = x + boxW - offsetX;
	int botY = y  + boxH - offsetY;
	
	auto& textboxComponents(manager->add_entity());


/*******************
 *  Top Left Corner
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		0, 0,
/*xpos			  : */		leftX,
/*ypos			  : */		topY, 
/*srcSize		  : */		tileSize,
/*destWidth		  : */		scale,
/*destHeight	  : */		scale,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id);


/*******************
 *  Top Right Corner
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		tileSize * 2, 0,
/*xpos			  : */		rightX,
/*ypos			  : */		topY,
/*srcSize		  : */		tileSize,
/*destWidth		  : */		scale,
/*destHeight	  : */		scale,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id
							);


/*******************
 *  Bottom Left Corner
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		0, tileSize * 2,
/*xpos			  : */		leftX,
/*ypos			  : */		botY, 
/*srcSize		  : */		tileSize,
/*scaleWidth	  : */		scale, 
/*scaleHeight	  : */		scale,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id
							);


/*******************
 *  Bottom Right Corner
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		tileSize * 2, tileSize * 2, 
/*xpos			  : */		rightX,
/*ypos			  : */		botY,
/*srcSize		  : */		tileSize,
/*destWidth		  : */		scale,
/*destHeight	  : */		scale,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id
							);


/*******************
 *  Top Edge
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		tileSize, 0,
/*xpos			  : */		leftX + scaledSize, 
/*ypos			  : */		topY, 
/*srcSize		  : */		tileSize, 
/*destWidth		  : */		( 2 * boxW - scaledSize ) / tileSize,
/*destHeight	  : */		scale,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id
							);


/*******************
 *  Left Edge
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		0, tileSize,
/*xpos			  : */		leftX, 
/*ypos			  : */		topY + scaledSize,
/*srcSize		  : */		tileSize, 
/*destWidth		  : */		scale, 
/*destHeight	  : */		( 2 * boxH - scaledSize ) / tileSize,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id
							);


/*******************
 *  Right Edge
 *******************/						
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY	  : */		tileSize * 2, tileSize,
/*xpos			  : */		rightX, 
/*ypos			  : */		topY + scaledSize,
/*srcSize		  : */		tileSize,
/*destWidth		  : */		scale,
/*destHeight	  : */		( 2 * boxH - scaledSize ) / tileSize,
/*rots, flipX, ID : */		0, SDL_FLIP_NONE, id
							);


/*******************
 *  Bottom Edge
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY  : */		tileSize, tileSize * 2, 
/*xpos		  : */		leftX + scaledSize, 
/*ypos		  : */		botY,
/*srcSize	  : */		tileSize,
/*destWidth   : */		( 2 * boxW - scaledSize ) / tileSize ,
/*destHeight  : */		scale,
/*rots, flipX : */		0, SDL_FLIP_NONE, id
						);


/*******************
 *  Body
 *******************/
	textboxComponents.add_component<Components::TextBoxComponent>(
/*srcX, srcY  : */		tileSize, tileSize, 
/*xpos		  : */		leftX + scaledSize, 
/*ypos		  : */		topY + scaledSize, 
/*srcSize	  : */		tileSize, 
/*destWidth   : */		( 2 * boxW - scaledSize ) / tileSize,
/*destHeight  : */		( 2 * boxH - scaledSize ) / tileSize,
/*rots, flipX : */		0, SDL_FLIP_NONE, id
						);

	textboxComponents.add_group(Game::groupTextBoxes);

}
//TODO move these abominations
void AssetManager::CreateTextBox(int x, int y, int width, int height, int offsetX, int offsetY, int scale, std::string text)
{
	std::string id = "textbox";
	SDL_Color black = { 0, 0, 0, 0 };
	int tileSize = 10;
	int scaledSize = tileSize * scale;
	int boxW = scaledSize * width / 2;
	int boxH = scaledSize * height / 2;
	int leftX = x - boxW - offsetX;
	int topY = y - boxH - offsetY;
	int rightX = x + boxW - offsetX;
	int botY = y + boxH - offsetY;
	
	CreateBox(x, y, width, height, offsetX, offsetY, scale, id);

	auto& textboxComponents(manager->add_entity());

	if (y > botY)
	{
		int speechX = x;
		if (x > rightX - scaledSize)
			speechX = rightX - scaledSize;
		if (x < leftX + scaledSize)
			speechX = leftX + scaledSize;
		/*******************
		*  Speech Bubble Bottom
		*******************/
		textboxComponents.add_component<Components::TextBoxComponent>(
			/*srcX, srcY  : */		0, tileSize * 3,
			/*xpos		  : */		speechX,
			/*ypos		  : */		botY,
			/*srcSize	  : */		tileSize,
			/*destWidth   : */		scale,
			/*destHeight  : */		scale,
			/*rots, flipX : */		0, SDL_FLIP_NONE, id
			);
	}
	else if (y < topY)
	{
		int speechX = x;
		if (x > rightX - scaledSize)
			speechX = rightX - scaledSize;
		if (x < leftX + scaledSize)
			speechX = leftX + scaledSize;
		/*******************
		*  Speech Bubble Top
		*******************/
		textboxComponents.add_component<Components::TextBoxComponent>(
			/*srcX, srcY  : */		tileSize * 2, tileSize * 3,
			/*xpos		  : */		speechX,
			/*ypos		  : */		topY,
			/*srcSize	  : */		tileSize,
			/*destWidth   : */		scale,
			/*destHeight  : */		scale,
			/*rots, flipX : */		0, SDL_FLIP_NONE, id
			);
	}
	else if (x > rightX)
	{
		int speechY = y;
		if (y > botY - scaledSize)
			speechY = botY - scaledSize;
		if (y < topY + scaledSize)
			speechY = topY + scaledSize;
		/*******************
		*  Speech Bubble Right
		*******************/
		textboxComponents.add_component<Components::TextBoxComponent>(
			/*srcX, srcY  : */		tileSize, tileSize * 3,
			/*xpos		  : */		rightX,
			/*ypos		  : */		speechY,
			/*srcSize	  : */		tileSize,
			/*destWidth   : */		scale,
			/*destHeight  : */		scale,
			/*rots, flipX : */		0, SDL_FLIP_NONE, id
			);
	}
	else if (x < leftX)
	{
		int speechY = y;
		if (y > botY - scaledSize)
			speechY = botY - scaledSize;
		if (y < topY + scaledSize)
			speechY = topY + scaledSize;
		/*******************
		*  Speech Bubble Right
		*******************/
		textboxComponents.add_component<Components::TextBoxComponent>(
			/*srcX, srcY  : */		tileSize, tileSize * 3,
			/*xpos		  : */		leftX,
			/*ypos		  : */		speechY,
			/*srcSize	  : */		tileSize,
			/*destWidth   : */		scale,
			/*destHeight  : */		scale,
			/*rots, flipX : */		0, SDL_FLIP_HORIZONTAL, id
			);
	}


	textboxComponents.add_component<Components::UILabel>(leftX + scaledSize, topY + scaledSize, text, "gilsans", black);
	textboxComponents.add_group(Game::groupTextBoxes);
}

//TODO move these abominations
void AssetManager::CreateTextBox(int x, int y, TTF_Font* font, std::string text)
{}

//TODO move these abominations
void AssetManager::CreateMenu(int x, int y)
{
	CreateBox(x, y, 10, 10, 0, 0, 1, "textbox");
	CreateBox(x, y+30, 10, 10, 0, 0, 1, "textbox");
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::load_texture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font * AssetManager::GetFont(std::string id)
{
	return fonts[id];
}

