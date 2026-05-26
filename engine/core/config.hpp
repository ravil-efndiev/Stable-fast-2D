#pragma once

namespace s2f 
{
	enum class LogMode : uint8_t
	{
		Normal, Verbose, None
	};

	struct GlobalConfig
	{
		LogMode logMode{ LogMode::Normal };
	};

	namespace globals
	{
		inline GlobalConfig gConfig{};
	}
}
