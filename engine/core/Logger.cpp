#include "Logger.hpp"
#include <chrono>

namespace s2f
{
	LogMode Logger::sLogMode{ LogMode::Normal };
	std::ofstream Logger::sLogFile;
	bool Logger::sSaveToFile{ false };

	void Logger::setLogFile(const std::filesystem::path& path)
	{
		sLogFile.open(path, std::ios::app);
		sLogFile << '\n' << "Starting to save logs at " << getTimeString() << '\n\n';
		sSaveToFile = true;
	}

	void Logger::writeAndSave(std::string_view prefix, std::string_view text, const char* prefixColor)
	{
		std::cout << prefixColor << prefix << COL_WHITE << text << '\n';

		if (sLogFile.is_open() && sSaveToFile)
		{
			sLogFile << '[' << getTimeString() << ']' << prefix << text << '\n';
		}
	}

	std::string Logger::getTimeString()
	{
		time_t time = std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()
		);

		tm localTime{};

#ifdef _WIN32
		localtime_s(&localTime, &time);
#else
		localtime_r(&time, &localTime);
#endif
		std::ostringstream ss;
		ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return ss.str();
	}
}
