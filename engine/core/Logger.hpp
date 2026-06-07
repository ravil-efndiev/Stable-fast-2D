#pragma once
#include <format>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace s2f
{
	constexpr auto COL_RED{ "\033[31m" };
	constexpr auto COL_GREEN{ "\033[32m" };
	constexpr auto COL_YELLOW{ "\033[33m" };
	constexpr auto COL_WHITE{ "\033[37m" };

	/*
	* @brief Enum that tells Logger what logs to write and save
	* 
	* Normal - basic info logs, warnings and errors are logged
	* 
	* Verbose - all from Normal + extra info including object lifetime  logs and spceific function calls is logged
	* 
	* None - nothing is logged, including errors and warnings - should be used in dist build only
	*/
	enum class LogMode : uint8_t
	{
		Normal, Verbose, None
	};
	
	/*
	* @brief Global static logger class responsible for logging based on log mode and saving logs to a file
	*/
	class Logger
	{
	public:
		template<class... Args>
		static void info(std::format_string<Args...> fmt, Args&&... args)
		{
			if (sLogMode == LogMode::None) return;
			writeAndSave("[Info] ", std::format(fmt, std::forward<Args>(args)...), COL_GREEN);
		}

		template<class... Args>
		static void vinfo(std::string_view fmt, Args&&... args)
		{
			if (sLogMode == LogMode::None) return;
			writeAndSave("[Info] ", std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)), COL_GREEN);
		}

		template<class... Args>
		static void warn(std::format_string<Args...> fmt, Args&&... args)
		{
			if (sLogMode == LogMode::None) return;
			writeAndSave("[Warn] ", std::format(fmt, std::forward<Args>(args)...), COL_YELLOW);
		}

		template<class... Args>
		static void vwarn(std::string_view fmt, Args&&... args)
		{
			if (sLogMode == LogMode::None) return;
			writeAndSave("[Warn] ", std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)), COL_YELLOW);
		}

		template<class... Args>
		static void error(std::format_string<Args...> fmt, Args&&... args)
		{
			if (sLogMode == LogMode::None) return;
			writeAndSave("[Error] ", std::format(fmt, std::forward<Args>(args)...), COL_RED);
		}

		template<class... Args>
		static void verror(std::string_view fmt, Args&&... args)
		{
			if (sLogMode == LogMode::None) return;
			writeAndSave("[Error] ", std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)), COL_RED);
		}

		template<class... Args>
		static void infoVerbose(std::format_string<Args...> fmt, Args&&... args)
		{
			if (sLogMode != LogMode::Verbose) return;
			info(fmt, std::forward<Args>(args)...);
		}

		static void setLogMode(LogMode mode) { sLogMode = mode; }
		static LogMode logMode() { return sLogMode; }

		/*
		* @brief Opens a file to save logs to, sets useLogFile flag to true
		* @param path path to a log file
		*/
		static void setLogFile(const std::filesystem::path& path);

		/*
		* @brief Sets flag to use log file to save logs to or no
		* 
		* Does nothing if log file path isn't set
		*/
		static void useLogFile(bool flag) { sSaveToFile = flag; }

	private:
		static void writeAndSave(std::string_view prefix, std::string_view text, const char* prefixColor);

		static std::string getTimeString();

	private:
		static LogMode sLogMode;
		static std::ofstream sLogFile;
		static bool sSaveToFile;
	};
}
