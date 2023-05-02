#include "component_creator.h"
#include "component_factory.h"


// Here to prevent including component_factory in the header file
void fen::ComponentCreatorBase::add_factory(const std::uint32_t& id, const std::size_t str_id, ComponentCreatorBase* creator)
{
	ComponentFactory::GetInstance()->AddFactory(id, str_id, creator);
}
