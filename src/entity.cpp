#include "entity.h"

#include <iostream>

#include "component_factory.h"

fen::Entity::Entity(): comps(ComponentFactory::Instance()->GetNumComps(), nullptr), active_comps(), comps_to_remove()
{
}

fen::Entity::~Entity()
{
	if (!moved)
	{
		std::cout << "destroy entity\n";
		for (auto& comp : active_comps)
		{
			delete comp;
		}
	}
}

void fen::Entity::init()
{
	for(auto it = active_comps.begin(); it != active_comps.end(); ++it)
	{
		(*it)->setOwner(this, it);
		(*it)->Init();
	}
}

void fen::Entity::update(const double dt)
{
	for (auto& comp : active_comps)
	{
		comp->Update(dt);
	}
}

void fen::Entity::purge()
{
	while(!comps_to_remove.empty())
	{
		const auto& comp = comps_to_remove.back();

		active_comps.erase(comps[comp]->active_comp_it);
		comps[comp]->Destroy();
		comps[comp] = nullptr;

		comps_to_remove.pop_back();
	}

	if (erase_on_no_components && active_comps.empty())
		erase = true;
}

void fen::Entity::Destroy()
{
	for (auto& comp : active_comps)
	{
		delete comp;
	}
	std::fill(comps.begin(), comps.end(), nullptr);
	active_comps.clear();
	comps_to_remove.clear();

	erase = true;
}
