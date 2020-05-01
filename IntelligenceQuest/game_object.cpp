#include "stdafx.h"
#include "game_object.h"


GameObject::GameObject() : active_(true), update_paused_(false), render_paused_(false)
{}

GameObject::~GameObject()
{
	render_commands_.clear();
	update_commands_.clear();
	registered_commands_.clear();
}

bool GameObject::is_active() const
{
	return active_;
}

void GameObject::deactivate()
{
	active_ = false;
}

void GameObject::add_group(Group group)
{
	group_bit_set_[group] = true;
	Manager::add_to_group(this, group);
}

void GameObject::remove_group(Group group)
{
	group_bit_set_[group] = false;
}

bool GameObject::has_group(Group group)
{
	return group_bit_set_[group];
}

void GameObject::update()
{
	if (update_paused_) return;

	for (auto& u : update_commands_)
		u->execute();
}

void GameObject::render()
{
	if (render_paused_) return;

	for (auto& r : render_commands_)
		r->execute();
}

void GameObject::clean()
{
	update_commands_.erase(std::remove_if(std::begin(update_commands_), std::end(update_commands_),
		[](const std::unique_ptr<Command> &command)
		{
			return command->is_terminated;
		}),
		std::end(update_commands_));

	render_commands_.erase(std::remove_if(std::begin(render_commands_), std::end(render_commands_),
		[](const std::unique_ptr<Command> &command)
		{
			return command->is_terminated;
		}),
		std::end(render_commands_));
}

void GameObject::pause_update()
{
	update_paused_ = !update_paused_;
}

void GameObject::pause_render()
{
	render_paused_ = !render_paused_;
}

bool GameObject::is_update_paused() const
{
	return update_paused_;
}

bool GameObject::is_render_paused() const
{
	return render_paused_;
}

Command* GameObject::add_update_command(Command * command) 
{
	std::unique_ptr<Command> u_ptr(command);
	update_commands_.push_back(std::move(u_ptr));
	return u_ptr.get();
}

Command* GameObject::add_render_command(Command * command)
{
	std::unique_ptr<Command> r_ptr(command);
	render_commands_.push_back(std::move(r_ptr));
	return r_ptr.get();
}

const std::vector<std::unique_ptr<Command>>* GameObject::get_render_commands() const
{
	return &render_commands_;
}

const std::vector<std::unique_ptr<Command>>* GameObject::get_update_commands() const
{
	return &update_commands_;
}

void GameObject::register_command(std::string command_id, Command * command)
{
	registered_commands_.emplace(command_id, command);
}

Command * GameObject::get_command(const std::string command_id)
{
	if (registered_commands_.find(command_id) == registered_commands_.end())
		return nullptr;

	return registered_commands_[command_id].get();
}

void GameObject::remove_command(const std::string command_id)
{
	if (registered_commands_.find(command_id) == registered_commands_.end())
		return;

	registered_commands_[command_id].get()->is_terminated = true;
	registered_commands_.erase(command_id);
}