#pragma once

#include <unordered_map>
#include <vector>

#include "singleton.h"
#include "component.h"

namespace fen
{
class ComponentFactory: public Singleton<ComponentFactory>
{
	friend Singleton;
	friend class Engine;
	 
	friend class ComponentCreatorBase;

	// Requires that D is derived from B and D != B
	template <typename B, typename D>
	using strictly_derived_check = std::enable_if_t< std::is_base_of_v<B, D> && !std::is_same_v<B, D>, bool >;

protected:

	void AddFactory(const std::uint32_t comp_id, const std::size_t str_id, ComponentCreatorBase* creator)
	{
		// assert that it has never been added before
		assert(id_create_funcs.size() == comp_id);
		(void(comp_id));
		id_create_funcs.push_back(creator);
		str_create_funcs.insert(std::make_pair(str_id, creator));
	}

public:

	/**
	 * \brief Returns a new Comp from a default copy of Comp
	 * \tparam Comp The component type. Must derive from Component
	 * \return Uses new!!! This class does NOT manage the deletion of the returned component
	 */
	template<class Comp, strictly_derived_check<Component, Comp> = true>
	[[nodiscard]] Comp* CreateComponent() const
	{
		return static_cast<Comp*>(create_component_Impl(Component::ID<Comp>()));
	}

	/**
	 * \brief Returns a new Component from a default copy of the component str name.
	 * \param str Must match a component type name
	 * \return Uses new!!! This class does NOT manage the deletion of the returned component
	 */
	[[nodiscard]] Component* CreateComponent(const char* str, std::uint32_t& c_id) const
	{
		return create_component_Impl(str, c_id);
	}

private:

	[[nodiscard]] Component* create_component_Impl(const std::uint32_t id) const;
	[[nodiscard]] Component* create_component_Impl(const char* str, std::uint32_t& c_id) const;

protected:
	
	std::vector<ComponentCreatorBase*> id_create_funcs;
	std::unordered_map<std::size_t, ComponentCreatorBase*> str_create_funcs;
public:

	virtual ~ComponentFactory() override;

	// Singleton requirements
	ComponentFactory(const ComponentFactory& other) = delete;
	ComponentFactory& operator=(const ComponentFactory& other) = delete;
	ComponentFactory(ComponentFactory&& other) = delete;
	ComponentFactory& operator=(ComponentFactory&& other) = delete;

protected:

	/**
	 * \brief A more traditional GetInstance from a Singleton design pattern. Used when you cannot ensure order of creation
	 * \return always an instance
	 */
	[[nodiscard]] static ComponentFactory* GetInstance()
	{
		if(instance_ == nullptr)
			instance_.reset(new ComponentFactory());

		return static_cast<ComponentFactory*>(instance_.get()); 
	}

	ComponentFactory() = default;

public:

	/**
	 * \return number of generated components
	 */
	[[nodiscard]] size_t GetNumComps() const { return id_create_funcs.size(); }
};

} // namespace fen