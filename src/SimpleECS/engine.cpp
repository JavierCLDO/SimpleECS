#include "engine.h"
#include <chrono>

#include "component_factory.h"

INIT_INSTANCE_STATIC(fen::Engine);

fen::Engine::~Engine()
{
	for(auto& e : entities)
	{
		e.Destroy();
	}
}

void fen::Engine::run()
{
	profiler.start_timing<Steps_Enum::Init>();

	test_create_unknown_comp();

	// Initialize starting entities
	while(!entities_to_add.empty())
	{
		entities.emplace_back(std::move(entities_to_add.front()));
		entities_to_add.pop();
		entities.back().init();
	}

	// For delta time calculation
	using hr_clock = std::chrono::high_resolution_clock;
	auto t_start = hr_clock::now();
	double dt;
	bool some_comps;

	profiler.finish_timing<Steps_Enum::Init>();

	while(!exit_)
	{
		profiler.start_timing<Steps_Enum::Update>();

		dt = std::chrono::duration<double>(hr_clock::now() - t_start).count();
		t_start = hr_clock::now();

		// Update cycle
		for (auto& e : entities)
		{
			e.update(dt);
		}

		profiler.finish_timing<Steps_Enum::Update>();

		profiler.start_timing<Steps_Enum::Purge>();

		some_comps = false;

		// purge components
		for(auto it = entities.begin(); it != entities.end(); ++it)
		{
			it->purge();
			if(it->erase)
				entities_to_remove.emplace(it);

			some_comps = some_comps || !it->has_no_components();
		}

		// purge entities
		while (!entities_to_remove.empty())
		{
			auto& e = entities_to_remove.front();
			e->Destroy();
			entities.erase(e);
			entities_to_remove.pop();
		}

		// add and initialize created entities
		while (!entities_to_add.empty())
		{
			entities.emplace_back(std::move(entities_to_add.front()));
			entities_to_add.pop();
			entities.back().init();

			some_comps = some_comps || !entities.back().has_no_components();
		}

		profiler.finish_timing<Steps_Enum::Purge>();

		// If user marked exit, or there are no entities left, or there are no components in any entity, stop execution
		exit_ = exit_ || entities.empty() || !some_comps;

		profiler.next_step();
	}

	printf("Time spent on Init: %.3f %s\n", profiler.get_time<Steps_Enum::Init>(), profiler.unit());
	printf("Avg Time spent on Update: %.3f %s\n", profiler.get_avg_time<Steps_Enum::Update>(), profiler.unit());
	printf("Avg Time spent on Purge: %.3f %s\n", profiler.get_avg_time<Steps_Enum::Purge>(), profiler.unit());
}

void fen::Engine::test_create_unknown_comp()
{
	auto engine = fen::Engine::Instance();

	auto& e = engine->add_entity();
	e.set_erase_on_no_components(true);

	//e.add_component<MyComponent>(); // Cannot add a component that the user defines (Im in the engine .lib!)

	// Add a component that the user 'tells me' that it should exist
	e.add_component("MyComponent_2");

	// fen does find this component because it isn't created in the user code
	e.add_component("MyComponent_22");
}
