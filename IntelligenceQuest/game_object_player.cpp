#include "stdafx.h"
#include "game_object_player.h"
#include "command_movement.h"
#include "command_camera.h"
#include "command_frame_animation.h"
#include "command_movement_animation.h"
#include "command_dynamic_render.h"
#include "command_controller_pause.h"
#include "command_controller_check_action.h"
#include "command_controller_move.h"

GameObjects::Player::Player(glm::vec2 position, int player_width, int player_height, float scale, float speed)
	: position_(position), player_width_(player_width), player_height_(player_height), scale_(scale), speed_(speed), entity(&Manager::add_entity())
{
	transform = &entity->add_component<Components::Transform>(position_.x, position_.y, player_width_, player_height_, scale_);
	render = &entity->add_component<Components::Render>("player", new SDL_Rect{ static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(player_width_ * scale_), static_cast<int>(player_height_ * scale_) }, new SDL_Rect{0, 0, player_width_, player_height_ });
	collision = &entity->add_component<Components::Collision>("player");
	frame_animation = &entity->add_component<Components::FrameAnimation>();
	movement = &entity->add_component<Components::Movement>(speed_);

	this->add_update_command(new Commands::PlayerMove(movement));
	this->add_update_command(new Commands::CheckAction());
	this->add_update_command(new Commands::Pause());
	this->add_update_command(new Commands::Movement(movement, transform));
	this->add_update_command(new Commands::Camera(transform));
	this->add_update_command(new Commands::MovementAnimation(movement, frame_animation));
	this->add_update_command(new Commands::FrameAnimation(frame_animation, render));

	this->add_render_command(new Commands::DynamicRender(render, transform));
	this->add_group(Game::group_players);
}

GameObjects::Player::~Player()
{
	this->remove_group(Game::group_players);
	this->deactivate();
}

