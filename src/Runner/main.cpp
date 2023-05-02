#include "engine.h"
#include "example_component.h"

void create_entities()
{
	auto engine = fen::Engine::Instance();

	auto& e = engine->add_entity();
	e.set_erase_on_no_components(true);

	// Add a component knowing the type at compilation time. Used when the component is known at compilation time
	e.add_component<MyComponent>();

	// Add a component without knowing it exists. Used when the engine does not know every component. For example, when the engine is used as a library and the components to add, read from a file and compiled in another project
	e.add_component("MyComponent_2");

	// fen does not add a non existent component
	e.add_component("MyComponent_22");
}

int main(void)
{
	fen::Engine::CreateInstance();

	//create_entities();

	fen::Engine::Instance()->run();

	return 0;
}