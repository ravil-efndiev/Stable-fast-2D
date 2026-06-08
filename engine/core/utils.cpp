#include "utils.hpp"

namespace s2f
{
	std::string getTextFromFile(const std::filesystem::path& path)
	{
		std::ifstream file(path.string());
		S2F_ASSERT(file.is_open(), "Failed to open file: " + path.string());

		std::stringstream fileData;
		fileData << file.rdbuf();
		return fileData.str();
	}

	std::string getVersionString(const Version& version)
	{
		return std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.patch);
	}

	std::string getVersionStringGLSL(const Version& version)
	{
		return std::to_string(version.major) + std::to_string(version.minor) + "0";
	}

}
