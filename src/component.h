#pragma once

#include <cstdint>

#include <list>

namespace fen
{
class Entity;

class Component
{
friend Entity; // Friend to protect user from calling the engine related functions

public:

	virtual ~Component() = default;

	Component() = default;
	Component(Component&& c) = default;

protected:

	/**
	 * \brief Called before the update cycle starts
	 */
	virtual void Init() = 0;


	/**
	 * \brief Called every update cycle
	 * \param dt delta time in seconds
	 */
	virtual void Update(const double dt) = 0;

public:

	/**
	 * \brief Called when the component is destroyed
	 */
	virtual void Destroy() = 0;

	template <typename T>
	static uint32_t ID() noexcept
	{
		static uint32_t t_id = id++;
		return t_id;
	}

protected:

	void setOwner(Entity* e, const std::list<Component*>::iterator& active_comp_it_) { owner = e; active_comp_it = active_comp_it_; }

	Entity* owner{ nullptr };

private:
	std::list<Component*>::iterator active_comp_it{};

	static uint32_t id;
};

}