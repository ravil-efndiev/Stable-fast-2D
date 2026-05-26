#pragma once
#include <format>
#include <iostream>
#include "config.hpp"

namespace s2f
{
	constexpr auto COL_RED = "\033[31m";
	constexpr auto COL_GREEN = "\033[32m";
	constexpr auto COL_YELLOW = "\033[33m";
	constexpr auto COL_WHITE = "\033[37m";

	namespace log
	{
		template<class... Args>
		inline void info(std::format_string<Args...> fmt, Args&&... args)
		{
			if (globals::gConfig.logMode == LogMode::None) return;
			std::cout << COL_GREEN << "[Info] " << COL_WHITE << std::format(fmt, std::forward<Args>(args)...) << '\n';
		}

		template<class... Args>
		inline void vinfo(std::string_view fmt, Args&&... args)
		{
			if (globals::gConfig.logMode == LogMode::None) return;
			std::cout << COL_GREEN << "[Info] " << COL_WHITE << std::vformat(fmt, std::make_format_args(args...)) << '\n';
		}

		template<class... Args>
		inline void warn(std::format_string<Args...> fmt, Args&&... args)
		{
			if (globals::gConfig.logMode == LogMode::None) return;
			std::cout << COL_YELLOW << "[Warn] " << COL_WHITE << std::format(fmt, std::forward<Args>(args)...) << '\n';
		}

		template<class... Args>
		inline void vwarn(std::string_view fmt, Args&&... args)
		{
			if (globals::gConfig.logMode == LogMode::None) return;
			std::cout << COL_YELLOW << "[Warn] " << COL_WHITE << std::vformat(fmt, std::make_format_args(args...)) << '\n';
		}

		template<class... Args>
		inline void error(std::format_string<Args...> fmt, Args&&... args)
		{
			if (globals::gConfig.logMode == LogMode::None) return;
			std::cerr << COL_RED << "[Error] " << COL_WHITE << std::format(fmt, std::forward<Args>(args)...) << std::endl;
		}

		template<class... Args>
		inline void verror(std::string_view fmt, Args&&... args)
		{
			if (globals::gConfig.logMode == LogMode::None) return;
			std::cerr << COL_RED << "[Error] " << COL_WHITE << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
		}

		template<class... Args>
		inline void infoVerbose(std::format_string<Args...> fmt, Args&&... args)
		{
			if (globals::gConfig.logMode != LogMode::Verbose) return;
			info(fmt, std::forward<Args>(args)...);
		}
	}
}
