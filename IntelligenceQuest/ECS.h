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
class GameObject;

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
	bool active_ = true;
	std::vector<std::unique_ptr<Component>> components_;

	ComponentArray component_array_;
	ComponentBitSet component_bit_set_;

public:
	Entity();
	~Entity();

	bool is_active() const;
	void destroy();

	template <typename T> bool has_component() const
	{
		return component_bit_set_[getComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs> T& add_component(TArgs&&... m_args)
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
	template<typename T> T& get_component() const
	{
		auto ptr(component_array_[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
	class System
	{
	public:
		static std::vector<GameObject*> organized_game_objects;

		System() = default;
		~System() = default;

		static void pause_update();
		static void pause_render();

		static void update();
		static void render();
	};

	Manager() = default;
	~Manager();
	static std::vector<std::unique_ptr<Entity>> entities_;
	static std::array<std::vector<std::unique_ptr<GameObject>>, maxGroups> grouped_game_objects_;
public:
	static void load_game_state(const char * file);
	static void write_game_state(const char * file);

	static void update();
	static void render();

	static void pause();
	static void minimize();

	static void refresh();
	static void add_to_group(GameObject* m_game_object, const Group m_group);

	static void add_group_to_system(Group group);
	static void clear_system();

	static Entity& add_entity();
};