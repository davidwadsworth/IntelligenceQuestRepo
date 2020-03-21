#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;
class System;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID last_id = 0u;
	return last_id++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID type_id = getNewComponentTypeID();
	return type_id;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public: 
	Entity * entity;

	virtual void init() {}
	virtual ~Component() {}
};

class Entity
{
private:
	Manager& manager_;
	bool active_ = true;
	std::vector<std::unique_ptr<Component>> components_;

	ComponentArray component_array_;
	ComponentBitSet component_bit_set_;
	GroupBitSet group_bit_set_;

public:
	explicit Entity(Manager& m_manager) : manager_(m_manager), component_array_()
	{}
	~Entity()
	{
		components_.erase(std::begin(components_), std::end(components_));
	}
	bool is_active() const { return active_; }
	void destroy() { active_ = false; }

	bool has_group(const Group m_group)
	{
		return group_bit_set_[m_group];
	}

	void add_group(Group m_group);
	void del_group(const Group m_group)
	{
		group_bit_set_[m_group] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return component_bit_set_[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& add_component(TArgs&&... m_args)
	{
		T* c(new T(std::forward<TArgs>(m_args)...));
		c->entity = this;
		std::unique_ptr<Component> u_ptr{ c };
		components_.emplace_back(std::move(u_ptr));

		component_array_[getComponentTypeID<T>()] = c;
		component_bit_set_[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(component_array_[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class System
{
private:
	bool active_ = true;
	std::vector<std::vector<Entity*>*> grouped_entities_;
public:
	Manager* manager;
	System() = default;
	virtual ~System() = default;
	bool is_active() const { return active_; }
	void add_grouped_entities(Group group);
	std::vector<std::vector<Entity*>*> get_grouped_entities();
	virtual void update() = 0;
};


class Manager
{
private:
	std::vector<std::unique_ptr<Entity>>entities_;
	std::array<std::vector<Entity*>, maxGroups> grouped_entities_;
	std::vector<std::unique_ptr<System>>render_systems_;
	std::vector<std::unique_ptr<System>>update_systems_;
public:

	void update()
	{
		for (auto& u : update_systems_) u->update();
	}

	void render()
	{
		for (auto& r : render_systems_) r->update();
	}


	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(grouped_entities_[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* m_entity)
			{
				return !m_entity->is_active() || !m_entity->has_group(i);
			}),
				std::end(v));

		}
		entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_),
			[](const std::unique_ptr<Entity> &m_entity)
		{
			return !m_entity->is_active();
		}),
			std::end(entities_));

		render_systems_.erase(std::remove_if(std::begin(render_systems_), std::end(render_systems_),
		[](const std::unique_ptr<System> &m_system)
		{
			return !m_system->is_active();
		}),
		std::end(render_systems_));

		update_systems_.erase(std::remove_if(std::begin(update_systems_), std::end(update_systems_),
			[](const std::unique_ptr<System> &m_system)
			{
				return !m_system->is_active();
			}),
			std::end(update_systems_));
	}

	void AddToGroup(Entity* m_entity, const Group m_group)
	{
		grouped_entities_[m_group].emplace_back(m_entity);
	}

	std::vector<Entity*>& getGroup(const Group m_group)
	{
		return grouped_entities_[m_group];
	}

	Entity& add_entity()
	{
		const auto e = new Entity(*this);
		std::unique_ptr<Entity> u_ptr{ e };
		entities_.emplace_back(std::move(u_ptr));
		return *e;
	}

	template <typename T, typename... TArgs>
	T* add_render_system(TArgs&&... m_args)
	{
		T* r(new T(std::forward<TArgs>(m_args)...));
		std::unique_ptr<System> u_ptr{ r };
		r->manager = this;
		render_systems_.emplace_back(std::move(u_ptr));
		return r;
	}

	template <typename T, typename... TArgs>
	T* add_update_system(TArgs&&... m_args)
	{
		T* u(new T(std::forward<TArgs>(m_args)...));
		std::unique_ptr<System> u_ptr{ u };
		u->manager = this;
		render_systems_.emplace_back(std::move(u_ptr));
		return u;
	}

};