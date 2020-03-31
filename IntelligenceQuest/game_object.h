#pragma once
#include "Game.h"
#include "command.h"

using GroupBitSet = std::bitset<maxGroups>;

class GameObject {
	std::map<std::string, std::unique_ptr<Command>> registered_commands_;

	std::vector<std::unique_ptr<Command>> update_commands_;
	std::vector<std::unique_ptr<Command>> render_commands_;
	bool active_, update_paused_, render_paused_;
	GroupBitSet group_bit_set_;
public:
	GameObject();
	virtual ~GameObject();

	bool is_active() const;
	void deactivate();

	void add_group(Group group);
	void remove_group(Group group);
	bool has_group(Group group);

	virtual void update();
	virtual void render();

	virtual void clean();

	void pause_update();
	void pause_render();

	bool is_update_paused() const;
	bool is_render_paused() const;

	void add_update_command(Command * command);
	void add_render_command(Command * command);

	const std::vector<std::unique_ptr<Command>>* get_render_commands() const;
	const std::vector<std::unique_ptr<Command>>* get_update_commands() const;

	void register_command(std::string command_id, Command * command);
	Command * get_command(const std::string command_id);
	void remove_command(const std::string command_id);
};
