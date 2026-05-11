#include "status.hpp"

namespace s2f
{
	Status statusSuccess()
	{
		return { true, "" };
	}

	Status statusError(const std::string& error)
	{
		return { false, error };
	}
}