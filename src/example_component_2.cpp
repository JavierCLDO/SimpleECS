#include "example_component_2.h"
#include <iostream>

#include "engine.h"

ADD_COMPONENT(MyComponent_2)

static int times = 5;

void MyComponent_2::Init()
{
	std::cout << "init\n";
	times--;
}

void MyComponent_2::Update(const double dt)
{
	std::cout << "comp2: updates left: " << counter-- << ", dt: " << dt << " s \n";


	if (counter < 0)
	{
		if (times > 0)
		{
			// The entities created from this component are not marked for deletion, but when they destroy themselves, the entity has no component. When there are no entity with a component, they get deleted
			auto& e = fen::Engine::Instance()->add_entity();
			e.add_component<MyComponent_2>();
		}

		owner->destroy_component<MyComponent_2>();

	}
}

void MyComponent_2::Destroy()
{
	std::cout << "destroy comp2\n";
}
