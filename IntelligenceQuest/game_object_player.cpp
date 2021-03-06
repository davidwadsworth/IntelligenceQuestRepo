#include "stdafx.h"
#include "game_object_player.h"
#include "command_force.h"
#include "command_camera_follow.h"
#include "command_frame_animation.h"
#include "command_movement_animation.h"
#include "command_render_dynamic.h"
#include "command_controller_pause.h"
#include "command_controller_check_action.h"
#include "command_controller_move.h"
#include "command_check_collision.h"
#include "command_refresh_quad_tree.h"
#include "collider_circle.h"

GameObjects::Player::Player(std::string tex, QuadTree* collision_tree, glm::vec2 position, int player_width, int player_height, float scale, float speed)
	: position_(position), player_width_(player_width), player_height_(player_height), scale_(scale), speed_(speed), entity(&Manager::add_entity()), collision_tree_(collision_tree)
{
	transform = &entity->add_component<Components::Transform>(position_.x, position_.y, player_width_, player_height_, scale_);
	render = &entity->add_component<Components::Render>(tex, new SDL_Rect{ static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(player_width_ * scale_), static_cast<int>(player_height_ * scale_) }, new SDL_Rect{0, 0, player_width_, player_height_ });
	collision = &entity->add_component<Components::Collision>("player", collision_tree_, new Colliders::Circle(&transform->position, glm::vec2(player_width_ * scale_ / 2.0f, player_height_ * scale_ / 2.0f), player_width_ / 2.0f));
	physics = &entity->add_component<Components::Physics>(1);
	frame_animation = &entity->add_component<Components::FrameAnimation>();
	movement = &entity->add_component<Components::Movement>(speed_);

	this->add_update_command(new ControllerCommands::Move(movement, physics));
	this->add_update_command(new ControllerCommands::CheckAction());
	this->add_update_command(new ControllerCommands::Pause());
	this->add_update_command(new Commands::MovementAnimation(physics, frame_animation));
	this->add_update_command(new Commands::CheckCollision(entity, collision, physics, transform));
	this->add_update_command(new Commands::Force(physics, transform));
	this->add_update_command(new Commands::CameraFollow(transform));
	this->add_update_command(new Commands::FrameAnimation(frame_animation, render));
	this->add_update_command(new Commands::RefreshQuadTree(entity, collision_tree_));

	this->add_render_command(new RenderCommands::Dynamic(render, transform));
	this->add_group(Game::group_players);

	collision_tree_->insert(entity);
}

GameObjects::Player::~Player()
{	
	this->remove_group(Game::group_players);
	this->deactivate();
}

