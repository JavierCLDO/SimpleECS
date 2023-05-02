#include "component_factory.h"

#include <iostream>

#include "component_creator.h"

INIT_INSTANCE_STATIC(fen::ComponentFactory);

fen::Component* fen::ComponentFactory::create_component_Impl(const std::uint32_t id) const
{
	return id_create_funcs[id]->operator()();
}

fen::Component* fen::ComponentFactory::create_component_Impl(const char* str, std::uint32_t& c_id) const
{
	const auto it = str_create_funcs.find(std::hash<std::string>().operator()(std::string(str)));

	// Runtime check instead of assert
	if(it != str_create_funcs.end())
	{
		c_id = it->second->get_id();
		return it->second->operator()();
	}
	else
	{
		std::cerr << str << " not found!\n";
		c_id = 0;
		return nullptr;
	}
}

fen::ComponentFactory::~ComponentFactory()
{
	for (const auto& c : id_create_funcs)
		delete c;
}
