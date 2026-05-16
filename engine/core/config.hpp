#pragma once

using u8 = uint8_t;

namespace s2f 
{
	enum class LogMode : u8
	{
		Normal, Verbose, None
	};

	struct GlobalConfig
	{
		LogMode logMode{ LogMode::Normal };
	};
}
