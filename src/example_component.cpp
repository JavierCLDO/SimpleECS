#include "example_component.h"
#include <iostream>

ADD_COMPONENT(MyComponent)

void MyComponent::Init()
{
	std::cout << "init\n";
}

void MyComponent::Update(const double dt)
{
	std::cout << "comp1: updates left: " << counter-- << ", dt: " << dt << " s \n";
	
	if (counter < 0)
		owner->destroy_component<MyComponent>();
}

void MyComponent::Destroy()
{
	std::cout << "destroy\n";
}
