#include "stdafx.h"

void Entity::add_group(Group m_group)
{
	group_bit_set_[m_group] = true;
	manager_.AddToGroup(this, m_group);
}

void System::add_grouped_entities(Group group)
{
	grouped_entities_.push_back(&manager->getGroup(group));
}

std::vector<std::vector<Entity*>*> System::get_grouped_entities()
{
	return grouped_entities_;
}
