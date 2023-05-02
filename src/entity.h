#pragma once

#include <list>

#include "component.h"
#include "component_factory.h"

#include <memory>
#include <vector>
#include <cassert>

namespace fen
{
class Entity
{
	friend class Engine; // Friend to protect user calling engine related functions (i.e: init, update, purge)

	// Requires that D is derived from B and D != B
	template <typename B, typename D>
	using strictly_derived_check = std::enable_if_t< std::is_base_of_v<B, D> && !std::is_same_v<B, D>, bool >;

public:

	Entity();
	~Entity();

	// User defined move constructor in order to prevent a moved entity to be destroyed (performance reasons)
	Entity(Entity&& e) noexcept : erase(e.erase), erase_on_no_components(e.erase_on_no_components),
	                              comps(std::move(e.comps)), active_comps(std::move(e.active_comps)),
	                              comps_to_remove(std::move(e.comps_to_remove))
	{
		if(!e.moved)
		{
			e.moved = true;
		}
	}

	/**
	 * \brief Checks whether this entity has a component
	 */
	template<typename Comp, strictly_derived_check<Component, Comp> = true>
	[[nodiscard]] bool has_component() const
	{
		assert(Component::ID<Comp>() < comps.size());
		return comps[Component::ID<Comp>()].get() != nullptr;
	}

	/**
	 * \brief Adds a component to this entity using a component known at compilation time
	 */
	template<typename Comp, strictly_derived_check<Component, Comp> = true>
	void add_component()
	{
		const auto comp = ComponentFactory::Instance()->CreateComponent<Comp>();
		const auto comp_id = Component::ID<Comp>();

		assert(comps[comp_id] == nullptr); // cannot add a component twice
		assert(comp != nullptr);

		active_comps.push_back(comp);
		comps[comp_id] = comp;
	}

	/**
	 * \brief Adds a component to this entity using a component which may be unknown at compilation time of this engine.
	 * (Useful when engine is compiled separately and the components are created from a data file)
	 * \param comp_str the component type as a string
	 */
	void add_component(const char* comp_str)
	{
		std::uint32_t comp_id;
		const auto comp = ComponentFactory::Instance()->CreateComponent(comp_str, comp_id);

		// Runtime check because it's using a str
		if(comp != nullptr && comps[comp_id] == nullptr)
		{
			active_comps.push_back(comp);
			comps[comp_id] = comp;
		}
	}

	/**
	 * \return A component if it has it. nullptr if it doesn't
	 */
	template <typename Comp, strictly_derived_check<Component, Comp> = true>
	[[nodiscard]] Comp* get_component() const
	{
		assert(Component::ID<Comp>() < comps.size());
		return comps[Component::ID<Comp>()];
	}

	/**
	 * \brief Marks a component for destruction after the update cycle
	 */
	template <typename Comp, strictly_derived_check<Component, Comp> = true>
	void destroy_component()
	{
		assert(Component::ID<Comp>() < comps.size());
		comps_to_remove.push_back(Component::ID<Comp>());
	}

	/**
	 * \brief Destroys this entity after the update cycle. Also destroys the components
	 */
	void Destroy();

private:

	void init();
	void update(const double dt);
	void purge();

	bool erase{ false };
	bool erase_on_no_components{ false };
	bool moved{ false };

	std::vector<Component*> comps;
	std::list<Component*> active_comps;
	std::list<std::uint32_t> comps_to_remove;

public:
	void set_erase_on_no_components(const bool b) { erase_on_no_components = b; }
	[[nodiscard]] bool has_no_components() const { return active_comps.empty(); }
};

}
