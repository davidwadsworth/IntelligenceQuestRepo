#include "stdafx.h"
#include "data_load_controller.h"
#include <rapidxml.hpp>
#include <fstream>
#include "controller.h"

DataLoads::LController::LController()
{}


DataLoads::LController::~LController() = default;

void DataLoads::LController::load(const char* path)
{
	std::ifstream mapFile(path);
	rapidxml::xml_document<> map;

	std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	map.parse<0>(&buffer[0]);

	const auto root_node = map.first_node("controller_map");

	const auto set_node = root_node->first_node("set");
	for (auto key_node = set_node->first_node("key"); key_node; key_node = key_node->next_sibling())
	{
		const auto key_id = key_node->first_attribute("key_id")->value();
		const auto key = atoi(key_node->first_attribute("key")->value());
		Controller::set_key(key, key_id);
	}
}


