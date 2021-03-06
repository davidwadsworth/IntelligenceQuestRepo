#include "stdafx.h"
#include "game_object.h"

std::vector< std::vector<std::unique_ptr<GameObject>>*> Manager::System::organized_game_objects;
std::vector<std::unique_ptr<Entity>> Manager::entities_;
std::array<std::vector<std::unique_ptr<GameObject>>, maxGroups> Manager::grouped_game_objects_;


Manager::~Manager()
{
	entities_.clear();
}

void Manager::load_game_state(const char * file)
{
	//TODO
}

void Manager::write_game_state(const char * file)
{
	//TODO
}

void Manager::update()
{
	System::update();
}

void Manager::render()
{
	System::render();
}

void Manager::pause()
{
	System::pause_update();
}


void Manager::minimize()
{
	System::pause_render();
	System::pause_update();
}

void Manager::refresh()

{
	for (auto i(0u); i < maxGroups; i++)
	{
		auto& v(grouped_game_objects_[i]);
		v.erase(
			std::remove_if(std::begin(v), std::end(v), [i](const std::unique_ptr<GameObject> &game_object)
				{
					return !game_object->is_active() || !game_object->has_group(i);
				}),
			std::end(v));

	}
	entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_),
		[](const std::unique_ptr<Entity> &m_entity)
		{
			return !m_entity->is_active();
		}),
		std::end(entities_));
}

void Manager::add_to_group(GameObject * m_game_object, const Group m_group)
{
	std::unique_ptr<GameObject> g_obj(m_game_object);
	grouped_game_objects_[m_group].emplace_back(std::move(g_obj));
}
void Manager::add_group_to_system(const Group group)
{
	System::organized_game_objects.push_back(&grouped_game_objects_[group]);
}

void Manager::clear_system()
{
	System::organized_game_objects.clear();
}

Entity & Manager::add_entity()
{
	const auto e = new Entity();
	std::unique_ptr<Entity> u_ptr{ e };
	entities_.emplace_back(std::move(u_ptr));
	return *e;
}

Manager::System::~System()
{
	organized_game_objects.clear();
};

void Manager::System::pause_update()
{
	for (auto group : System::organized_game_objects)
		for (auto& game_object : *group)
			game_object->pause_update();
}

void Manager::System::pause_render()
{
	for (auto group : System::organized_game_objects)
		for (auto& game_object : *group)
			game_object->pause_render();
}

void Manager::System::update()
{
	for (auto group : System::organized_game_objects)
		for (auto& game_object : *group)
			game_object->update();
}

void Manager::System::render()
{
	for (auto group : System::organized_game_objects)
		for (auto& game_object : *group)
			game_object->render();
}

Entity::Entity() : component_array_()
{}

Entity::~Entity()
{
	components_.clear();
}

bool Entity::is_active() const { return active_; }

void Entity::destroy() { active_ = false; }
