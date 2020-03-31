#pragma once

class Controller
{
	Controller() = default;
public:
	static int left;
	static int right;
	static int down;
	static int up;
	static int action_1;
	static int action_2;
	static int action_3;
	static int menu;

	static void set_key(int key, std::string key_id);
};
