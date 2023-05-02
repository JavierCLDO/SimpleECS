#pragma once

#include <cstdint>
#include <string>
#include <type_traits>

#include "component.h"

namespace fen
{
	
class ComponentCreatorBase
{
public:
	virtual ~ComponentCreatorBase() = default;
	virtual Component* operator()() = 0;
	[[nodiscard]] virtual std::uint32_t get_id() const = 0;
	void add_factory(const std::uint32_t& id, const std::size_t str_id, ComponentCreatorBase* creator);
};

template<class Comp>
class ComponentCreator : public ComponentCreatorBase
{
public:
	explicit ComponentCreator(const char* str)
	{
		add_factory(Component::ID<Comp>(), std::hash<std::string>().operator()(std::string(str)), this);
	}

	[[nodiscard]] std::uint32_t get_id() const override
	{
		return Component::ID<Comp>();
	}

	Comp* operator()() override
	{
		return new Comp();
	}
};

}

/**
 * \brief Adds a component to the engine component factory. Add this line to the .cpp file of your component
 * \param Comp The component class type
 */
#define ADD_COMPONENT(Comp) static auto factory_##Comp = new fen::ComponentCreator<Comp>(#Comp);
