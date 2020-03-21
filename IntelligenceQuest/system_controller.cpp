#include "stdafx.h"
#include "system_controller.h"
#include "component_animation.h"

UpdateSystems::Controller::Controller() = default;
UpdateSystems::Controller::~Controller() = default;

void UpdateSystems::Controller::update()
{
	for (auto g : get_grouped_entities())
	{
		for (auto& e : *g)
		{
			auto anim = &e->getComponent<Components::FrameAnimation>();
			auto transform = &e->getComponent<Components::Transform>();

			/***********
			 * Actions
			 ************/
			if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_Z))
			{
				switch (zaction % 2)
				{
				case 0:
					Game::assets->CreateTextBox(transform->position.x - Game::camera.x, transform->position.y - Game::camera.y, 15, 7, 50, 100, 2, "I am extremely intelligent");
					break;
				case 1:
					for (auto& t : manager->getGroup(Game::groupTextBoxes))
					{
						t->del_group(Game::groupTextBoxes);
					}
					break;
				default:
					break;
				}
				zaction++;
			}

			if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_X))
			{
				switch (xaction % 2)
				{
				case 0:
					Game::assets->CreateMenu(transform->position.x - Game::camera.x, transform->position.y - Game::camera.y);
					break;
				case 1:
					for (auto& t : manager->getGroup(Game::groupTextBoxes))
					{
						t->del_group(Game::groupTextBoxes);
					}
					break;
				default:
					break;
				}
				xaction++;
			}

			/***********
			* States
			************/
			transform->velocity = glm::vec2(0, 0);
			anim->is_animated = false;

			if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_UP) && Game::keyboard_handler.checkKeyState(SDL_SCANCODE_RIGHT))
			{
				anim->is_animated = true;
				anim->play("walk up right");
				transform->velocity.y = -0.75f;
				transform->velocity.x = 0.75f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_UP) && Game::keyboard_handler.checkKeyState(SDL_SCANCODE_LEFT))
			{
				anim->is_animated = true;
				anim->play("walk up left");
				transform->velocity.y = -0.75f;
				transform->velocity.x = -0.75f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_DOWN) && Game::keyboard_handler.checkKeyState(SDL_SCANCODE_RIGHT))
			{
				anim->is_animated = true;
				anim->play("walk down right");
				transform->velocity.y = 0.75f;
				transform->velocity.x = 0.75f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_DOWN) && Game::keyboard_handler.checkKeyState(SDL_SCANCODE_LEFT))
			{
				anim->is_animated = true;
				anim->play("walk down left");
				transform->velocity.y = 0.75f;
				transform->velocity.x = -0.75f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_UP))
			{
				anim->is_animated = true;
				anim->play("walk up");
				transform->velocity.y = -1.0f;
				transform->velocity.x = 0.0f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_DOWN))
			{
				anim->is_animated = true;
				anim->play("walk down");
				transform->velocity.y = 1.0f;
				transform->velocity.x = 0.0f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_RIGHT))
			{
				anim->is_animated = true;
				anim->play("walk right");
				transform->velocity.x = 1.0f;
				transform->velocity.y = 0.0f;
			}
			else if (Game::keyboard_handler.checkKeyState(SDL_SCANCODE_LEFT))
			{
				anim->is_animated = true;
				anim->play("walk left");
				transform->velocity.x = -1.0f;
				transform->velocity.y = 0.0f;
			}

		}
	}
}
