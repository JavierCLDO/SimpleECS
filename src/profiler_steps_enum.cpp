#include "profiler_steps_enum.h"


/**
 * \brief prefix ++ operator for the enum
 */
Steps_Enum& operator++(Steps_Enum& orig)
{
	orig = static_cast<Steps_Enum>(orig + 1); // static_cast required because enum + int -> int
	return orig;
}

/**
 * \brief Prints the enum name to the output stream
 */
std::ostream& operator<<(std::ostream& os, const Steps_Enum& e)
{
	switch (e)
	{
	case Steps_Enum::Init:		os << "Init"; break;
	case Steps_Enum::Update:	os << "Update"; break;
	case Steps_Enum::Purge:		os << "Purge"; break;
	case Steps_Enum::ALL_: break;
	}
	return os;
}
