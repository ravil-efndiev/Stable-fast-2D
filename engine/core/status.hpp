#pragma once
#include "include.hpp"

namespace s2f
{
	struct Status 
	{
		bool success;
		std::string error;
	};
	
	Status statusSuccess();
	Status statusError(const std::string& error);

	template <class ...Args>
	requires (std::same_as<std::decay_t<Args>, Status> && ...)
	bool checkStatuses(Args&& ...statuses)
	{
		std::vector<Status> statusVec{ std::forward<Args>(statuses)... };
		for (const auto& status : statusVec)
		{
			if (!status.success)
			{
				Logger::verror(status.error);
				return false;
			}
		}	
		return true;
	}
}
