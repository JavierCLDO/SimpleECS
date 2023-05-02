#pragma once

#include <list>
#include <chrono>
#include <queue>

#include "singleton.h"

#include "entity.h"
#include "simple_profiler.h"
#include "profiler_steps_enum.h"

namespace fen
{
	
class Engine : public Singleton<Engine>
{
	// Singleton requirements
	friend Singleton;

public:

	virtual ~Engine() override;

	// Singleton requirements
	Engine(const Engine& other) = delete;
	Engine& operator=(const Engine& other) = delete;
	Engine(Engine&& other) = delete;
	Engine& operator=(Engine&& other) = delete;


	/**
	 * \brief Cycles until the exit condition is fulfilled
	 */
	void run();

	/**
	 * \brief Adds an entity to the end of the list before the first cycle or after the update cycle
	 * \return returns the entity reference
	 */
	[[nodiscard]] Entity& add_entity()
	{
		entities_to_add.emplace();
		return entities_to_add.back();
	}

private:

	std::list<Entity> entities;
	std::queue<std::list<Entity>::iterator> entities_to_remove;
	std::queue<Entity> entities_to_add;

	bool exit_{false};

	SimpleProfiler<Steps_Enum::ALL_, double, std::milli> profiler;

	// Used to test that the engine can create a component for which it does not know how to make
	void test_create_unknown_comp();

protected:

	void exit() { exit_ = true; }

	Engine() = default;
};

} // namespace fen