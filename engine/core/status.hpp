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
	bool checkStatuses(Args&& ...statuses)
	{
		static_assert((std::is_same_v<std::decay_t<Args>, Status> && ...), 
			"All arguments of checkStatuses must be of type Status");

		std::vector<Status> statusVec{ std::forward<Args>(statuses)... };
		for (const auto& status : statusVec)
		{
			if (!status.success)
			{
				S2F_ERROR(status.error);
				return false;
			}
		}	
		return true;
	}
}
