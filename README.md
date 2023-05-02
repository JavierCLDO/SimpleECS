# SimpleECS
Simple ecs engine where each entity holds components

The engine uses a component factory, where the user adds the created component factory during static initilization. This component creator is then used by the component factory to create (use new operator) a user defined component, even though the engine may be compiled without knowing the existence of said component. There are examples of use in the [user components](src/Runner/) files and created in [engine file](src/SimpleECS/engine.cpp). The purpose of this factory is for the engine to be compiled separately as a library and then the world generated via the engine reading a file or via executing a script, where the component gets created from a string name (again, example in the [engine file](src/SimpleECS/engine.cpp))

The engine tries to be lightweight and fast where possible, but still providing the basic functionality of a non-pure ecs engine

There are no children entities or ways to get an entity from the engine other than creating the entity itself. 