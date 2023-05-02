#pragma once

#include "component_creator.h"
#include "component.h"
#include "entity.h"

// Defining a UserComponent to create a nice .h file with the helper .h files that are needed to correctly create and manage a user component
// Also, it may be needed in the future to add any virtual or helper method

namespace fen
{
class UserComponent : public fen::Component
{

};

}