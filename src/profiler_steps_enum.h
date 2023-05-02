#pragma once
#include <ostream>

/**
 * \brief Profiler steps
 */
enum Steps_Enum : unsigned {
	Init, Update, Purge,
	ALL_
};


/**
 * \brief prefix ++ operator for the enum
 */
Steps_Enum& operator++(Steps_Enum& orig);

/**
 * \brief Prints the enum name to the output stream
 */
std::ostream& operator<<(std::ostream& os, const Steps_Enum& e);